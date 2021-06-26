#include "process.h"
#include "lock.h"
#include "pagetable.h"
#include "elf.h"
#include "defs.h"
#include "memlayout.h"

extern const char binary_putc_start;
extern char trampoline[]; // trampoline.S
extern pagetable_t uvmcreate();
extern void uvmfree(pagetable_t pagetable, uint64 sz);
extern uint64 uvmalloc(pagetable_t pagetable, uint64 oldsz, uint64 newsz);

thread_t *running[NCPU];

struct cpu cpus[NCPU];

process_t proc[NPROC];
// process_t *initproc;
thread_t thre[NTHRE];

struct list_head sched_list[NCPU];
struct lock pidlock, tidlock, schedlock;
int _pid, _tid;


// 将ELF文件映射到给定页表的地址空间，返回pc的数值
// 关于 ELF 文件，请参考：https://docs.oracle.com/cd/E19683-01/816-1386/chapter6-83432/index.html
static uint64 load_binary(pagetable_t *target_page_table, const char *bin){
	struct elf_file *elf;
    int i;
    uint64 seg_sz, p_vaddr, seg_map_sz;
	elf = elf_parse_file(bin);
	uint64 sz = 0;
	//DEBUG("\n");
	/* load each segment in the elf binary */
	for (i = 0; i < elf->header.e_phnum; ++i) {
		if (elf->p_headers[i].p_type == PT_LOAD) {
            // 根据 ELF 文件格式做段映射
            // 从ELF中获得这一段的段大小
            seg_sz = elf->p_headers[i].p_memsz;
            // 对应段的在内存中的虚拟地址
            p_vaddr = elf->p_headers[i].p_vaddr;
            // 对映射大小做页对齐
			seg_map_sz = ROUNDUP(seg_sz + p_vaddr, PGSIZE) - PGROUNDDOWN(p_vaddr);
            // 接下来代码的期望目的：将程序代码映射/复制到对应的内存空间
            // 一种可能的实现如下：
            /* 
             * 在 target_page_table 中分配一块大小
             * 通过 memcpy 将某一段复制进入这一块空间
             * 页表映射修改
             */
            //DEBUG("\n");
            sz = uvmalloc(target_page_table, sz, p_vaddr + seg_map_sz);
            
            //DEBUG("\n");


		}
	}
    //DEBUG("\n");
	/* PC: the entry point */
	return elf->header.e_entry;
}

int alloc_pid() {
    int pid;
    acquire(&pidlock);
    pid = _pid;
    _pid = _pid + 1;
    release(&pidlock);
    return pid;
}

int alloc_tid() {
    int tid;
    acquire(&tidlock);
    tid = _tid;
    _tid = _tid + 1;
    release(&tidlock);
    return tid;
}

void proc_freepagetable(pagetable_t pagetable, uint64 sz) {
    uvmfree(pagetable, sz);
}

void free_proc(process_t *p) {
    if(p->pagetable)
        proc_freepagetable(p->pagetable, p->sz);
    p->pagetable = 0;
    p->sz = 0;
    p->pid = 0;
    p->parent = 0;
    p->name[0] = 0;
    p->killed = 0;
    p->xstate = 0;
    p->process_state = UNUSED;
}

void free_thre(thread_t *t) {
    if(t->trapframe)
        mm_kfree((void*)t->trapframe);
    t->trapframe = 0;
    
    t->tid = 0;
    t->process = 0;
    t->name[0] = 0;
    t->killed = 0;
    t->xstate = 0;
    t->thread_state = UNUSED;
}

pagetable_t proc_pagetable() {
    pagetable_t pagetable;
    pagetable = uvmcreate();
    if (pagetable == NULL)
        return NULL;
    
    if (pt_map_pages(pagetable, TRAMPOLINE, 
            (uint64)trampoline, PGSIZE, PTE_R | PTE_X) < 0) {
        uvmfree(pagetable, PGSIZE);
    }
    return pagetable;
}

thread_t *alloc_thread(process_t *p) {
    thread_t *t;
    for (t = thre; t < &thre[NTHRE]; t++) {
        acquire(&t->lock);
        if (t->thread_state == UNUSED) {
            goto found;
        } else {
            release(&t->lock);
        }
    }
    return NULL;
found:
    if ((t->trapframe = (struct trapframe *) mm_kalloc()) == NULL) {
        free_thre(t);
        release(&t->lock);
        return NULL;
    }

    if (pt_map_pages(p->pagetable, TRAPFRAME, 
            (uint64)t->trapframe, PGSIZE, PTE_R | PTE_W) < 0) {
        free_thre(t);
        uvmfree(p->pagetable, 1);
        p->pagetable = 0;
        release(&t->lock);
        return NULL;
    }

    memset(&t->context, 0, sizeof(t->context));
    // t->context.ra = (uint64)forkret;
    t->context.sp = t->kstack + PGSIZE;
    release(&t->lock);
    return t;
}

/* 分配一个进程，需要至少完成以下目标：
 * 
 * 分配一个主线程
 * 创建一张进程页表
 * 分配pid、tid
 * 设置初始化线程上下文
 * 设置初始化线程返回地址寄存器ra，栈寄存器sp
 * 
 * 这个函数传入参数为一个二进制的代码和一个线程指针(具体传入规则可以自己修改)
 * 此外程序首次进入用户态之前，应该设置好trap处理向量为usertrap（或者你自定义的）
 */

process_t *alloc_proc(const char* bin, thread_t *thr){
    process_t *p;
    DEBUG("\n");
    for (p = proc; p < &proc[NPROC]; p++) {
        acquire(&p->lock);
        if (p->process_state == UNUSED) {
            goto found;
        } else {
            release(&p->lock);
        }
    }
    DEBUG("\n");
    return NULL;

found:
    DEBUG("\n");
    p->pid = alloc_pid();
    p->process_state = IDLE;

    if ((p->pagetable = proc_pagetable()) == NULL) {
        free_proc(p);
        release(&p->lock);
        return NULL;
    }
    DEBUG("\n");
    if ((thr = alloc_thread(p)) == NULL) {
        free_proc(p);
        release(&p->lock);
        return NULL;
    }
    thread_t *t = thr;
    t->trapframe->epc = load_binary(&p->pagetable, bin);
    
    acquire(&t->lock);
    
    t->process = p;
    init_list_head(&p->thread_list);
    list_add(&t->process_list_thread_node, &p->thread_list);

    release(&t->lock);
    release(&p->lock);
    return p;
}



bool load_thread(file_type_t type){
    if(type == PUTC){
        thread_t *t = NULL;
        process_t *p = alloc_proc(&binary_putc_start, t);
        if(!t) return false;
        
        sched_enqueue(t);
        
    } else {
        BUG("Not supported");
    }
    return false;
}

// sched_enqueue和sched_dequeue的主要任务是加入一个任务到队列中和删除一个任务
// 这两个函数的展示了如何使用list.h中可的函数（加入、删除、判断空、取元素）
// 具体可以参考：Stackoverflow上的回答
// https://stackoverflow.com/questions/15832301/understanding-container-of-macro-in-the-linux-kernel
void sched_enqueue(thread_t *target_thread){
    if(target_thread->thread_state == RUNNING) BUG("Running Thread cannot be scheduled.");
    list_add(&target_thread->sched_list_thread_node, &(sched_list[cpuid()]));
}

thread_t *sched_dequeue(){
    if(list_empty(&(sched_list[cpuid()]))) BUG("Scheduler List is empty");
    thread_t *head = container_of(&(sched_list[cpuid()]), thread_t, sched_list_thread_node);
    list_del(&head->sched_list_thread_node);
    return head;
}

bool sched_empty(){
    return list_empty(&(sched_list[cpuid()]));
}

// 开始运行某个特定的函数
void thread_run(thread_t *target){
    acquire(&target->lock);
    if (target->thread_state == RUNNABLE) {
        target->thread_state = RUNNING;
        mycpu()->thread = target;
        swtch(&mycpu()->context, &target->context);
        mycpu()->thread = 0;
    }
    release(&target->lock);
}

// sched_start函数启动调度，按照调度的队列开始运行。
void sched_start(){
    mycpu()->thread = 0;

    while(1){
        if(sched_empty()) BUG("Scheduler list empty, no app loaded");
        thread_t *next = sched_dequeue();
        thread_run(next);
    }
}

void sched_init(){
    DEBUG("\n");
    // 初始化调度队列锁
    lock_init(&schedlock);
    // 初始化队列头
    init_list_head(&(sched_list[cpuid()]));
}

void proc_init(){
    // 初始化pid、tid锁
    lock_init(&pidlock);
    lock_init(&tidlock);
    // 接下来代码期望的目的：映射第一个用户线程并且插入调度队列
    DEBUG("\n");
    if(!load_thread(PUTC)) BUG("Load failed");
}

struct cpu* mycpu(void) {
    int id = cpuid();
    struct cpu *c = &cpus[id];
    return c;
}

struct thread* mythread(void) {
    push_off();
    struct cpu *c = mycpu();
    struct thread *t = c->thread;
    pop_off();
    return t;
}

void sched(void) {
    int intena;
    thread_t *t = mythread();    

    if (!is_locked(&t->lock))
        BUG("sched t->lock");
    if (mycpu()->noff != 1)
        BUG("sched locks");
    if (t->thread_state == RUNNING)
        BUG("sched running");
    if (intr_get())
        BUG("sched interruptible");

    intena = mycpu()->intena;

    swtch(&t->context, &mycpu()->context);
    mycpu()->intena = intena;
}

void yield(void){
    struct thread *t = mythread();
    acquire(&t->lock);
    t->thread_state = RUNNABLE;
    sched();
    release(&t->lock);
}

void exit(int status) {
    struct thread *t = mythread();

    
}

