void enable_paging() {
    // TODO: Homework 2: Enable paging
    // After initializing the page table, write to register SATP register for kernel registers.
    // Flush the TLB to invalidate the existing TLB Entries
    // Suggested: 2 LoCs
    w_satp(MAKE_SATP(kernel_pagetable));
    flush_tlb();
}

// Return the address of the PTE in page table *pagetable*
// The Risc-v Sv48 scheme has four levels of page table.
// For VA:
//   47...63 zero
//   39...47 -- 9  bits of level-3 index
//   30...38 -- 9  bits of level-2 index
//   21...29 -- 9  bits of level-1 index
//   12...20 -- 9  bits of level-0 index
//   0...11  -- 12 bits of byte offset within the page
// Return the last-level page table entry.
static pte_t* pt_query(pagetable_t pagetable, vaddr_t va, int alloc){
    if(va >= MAXVA) BUG_FMT("get va[0x%lx] >= MAXVA[0x%lx]", va, MAXVA);
    // Suggested: 18 LoCs
    pte_t *pte = NULL;
    //if (va == 0) DEBUG("here\n");
    for (uint i = 3; i >= 1; i--) {
        //if (va == 0) DEBUG("here\n");
        pte = pagetable + PX(i, va);
        //if (va == 0) DEBUG("here, pgt = %lx, pte = %lx, *pte = %lx\n", pagetable, pte, *pte);
        if (*pte == NULL) {
            //if (va == 0) DEBUG("here\n");
            if (alloc) 
                *pte = (pte_t) PA2PTE(mm_kalloc()) | PTE_V;
            else 
                return NULL;
        }
        //if (va == 0) DEBUG("here\n");
        pagetable = (pagetable_t) PTE2PA(*pte);
    }
    return pagetable + PX(0, va);
}

void pt_free(pagetable_t pagetable) {
    for (int i = 0; i < 512; i++) {
        pte_t pte = pagetable[i];
        if ((pte & PTE_V) && (pte & (PTE_R | PTE_W | PTE_X)) == 0) {
            uint64 child = PTE2PA(pte);
            pt_free((pagetable_t)child);
            pagetable[i] = 0;
        } else if (pte & PTE_V) {
            BUG("pt_free: leaf");
        }
    }
    mm_kfree((void *)pagetable);
}

int pt_map_pages(pagetable_t pagetable, vaddr_t va, paddr_t pa, uint64 size, int perm){
    // Suggested: 11 LoCs
    for (uint64 i = 0; i < size; i += PGSIZE)
        pt_map_addrs(pagetable, va + i, pa + i, perm);
    return 0; // Do not modify
}

void pt_unmap_pages(pagetable_t pagetable, uint64 va, uint64 size, int do_free) {
    pte_t *pte;
    for (uint64 i = 0; i < size; i += PGSIZE) {
        pte = pt_query(pagetable, va + i, 0);
        if (do_free) {
            uint64 pa = PTE2PA(*pte);
            mm_kfree((void*)pa);
        }
        *pte = 0;
    }
}

paddr_t pt_query_address(pagetable_t pagetable, vaddr_t va){
    //DEBUG("\n");
    pte_t pte = *pt_query(pagetable, va, 1);
    //DEBUG("\n");
    return PTE2PA(pte) | (va & (PGSIZE - 1));
}

int pt_unmap_addrs(pagetable_t pagetable, vaddr_t va){
    pte_t* pte = pt_query(pagetable, va, 0);
    if (pte != NULL) *pte = 0;
    return 0; // Do not modify
}

int pt_map_addrs(pagetable_t pagetable, vaddr_t va, paddr_t pa, int perm){
    //if (va == 0) DEBUG("here1, va = %lx\n", va);
    pte_t* pte = pt_query(pagetable, va, 1);
    //if (va == 0) DEBUG("here2");
    *pte = PA2PTE(pa) | perm;
    return 0; // Do not modify
}

pagetable_t uvmcreate() {
    pagetable_t pagetable;
    pagetable = (pagetable_t) mm_kalloc();
    if (pagetable == NULL)
        return NULL;
    memset(pagetable, 0, PGSIZE);
    return pagetable;
}

uint64 uvmdealloc(pagetable_t pagetable, uint64 oldsz, uint64 newsz) {
    if (newsz >= oldsz)
        return oldsz;
    if (PGROUNDUP(newsz) < PGROUNDUP(oldsz)) {
        int npages = (PGROUNDUP(oldsz) - PGROUNDUP(newsz)) / PGSIZE;
        pt_unmap_pages(pagetable, PGROUNDUP(newsz), npages * PGSIZE, 1);
    }

    return newsz;
}

uint64 uvmalloc(pagetable_t pagetable, uint64 oldsz, uint64 newsz) {
    char *mem;
    uint64 a;
    //DEBUG("oldsz = %lx, newsz = %lx\n", oldsz, newsz);
    if (newsz < oldsz)
        return oldsz;
    //DEBUG("\n");
    oldsz = PGROUNDUP(oldsz);
    for (a = oldsz; a < newsz; a += PGSIZE) {
        mem = mm_kalloc();
        //DEBUG("\n");
        if (mem == 0) {
            uvmdealloc(pagetable, a, oldsz);
            return 0;
        }
        //DEBUG("\n");
        memset(mem, 0, PGSIZE);
        //DEBUG("\n");
        if (pt_map_pages(pagetable, a, (uint64)mem, PGSIZE, PTE_W|PTE_X|PTE_R|PTE_U) != 0) {
            //DEBUG("\n");
            mm_kfree(mem);
            //DEBUG("\n");
            uvmdealloc(pagetable, a, oldsz);
            //DEBUG("\n");
            return 0;
        }
        //DEBUG("\n");
    }
    return newsz;
}

void uvmfree(pagetable_t pagetable, uint64 sz) {
    if (sz > 0) 
        pt_unmap_pages(pagetable, 0, sz, 1);
    pt_free(pagetable);
}