## 问题1：内核在哪里？
### (1) 尝试使用gdb单步跟踪内核的启动流程，并列出从启动qemu到进入到main函数的函数调用过程及其对应地址。Tips: 可以通过objdump查看生成elf的符号表，查询qemu的手册找到入点。

通过 rbreak 命令，将所有经过的函数全部打上断点，然后通过 continue 或者 next step 来逐步观察所有运行的指令，得到了以下进入mian函数时曾调用过的函数：

```bash
0x0000000080000000 in _entry ()
0x0000000080000902 void start()
0x000000008000001c in main ()
```

具体而言，就是从 ALIGN(0x1000)，跳转到 _entry，这是一段汇编代码。_entry 最终会调用 start，这里就是 c 语言编写的代码了。start 内部会调用许许多多的函数，最终通过一条 mret 的汇编指令跳转到 main 函数。

### (2) 指出如何使用gdb中的一条指令显示(1)所需要的内容。

(１) 中的方法可以打印出函数，但是使用 bt 指令只能显示 main 函数，目前还不太会只使用 bt 就打印出所有的函数

## 问题2：启动内核！在我们使用QEMU模拟中，内核是如何启动的？和编译脚本的关联是什么？

我们使用 make qemu-nox 之后，会调用 Makefile 中的 `$(QEMU) -nographic $(QEMUOPTS) 指令，展开之后得到的是：
```bash
qemu-system-riscv64 -nographic -machine virt -bios none -kernel $(BUILD_DIR)/kernel.img -m size=1G
```

也就是 qemu 启动的时候载入了 kernel.img 镜像

## 问题3: 内核输出内核输出函数和通过stdio中的printf函数输出到屏幕的过程差异有哪些？

printk 运行在内核态，printf 运行在用户态，他们都会调用 tty_write。这两个函数几乎是相同的，区别在tty_write这个函数让 fs 指向被显示的字符串，但 fs 是专门用于存放用户态字符串的，所以 printk 会将 fs指向 内核中的ds，这会额外增加一个压栈保存的操作。