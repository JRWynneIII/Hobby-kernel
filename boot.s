.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

#multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

#create the stack
.section .bootstrap_stack
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp
	cli
	mov %eax, %cr0
	or %al, 1
	mov %cr0, %eax
	call kernel_main
	hlt
.Lhang:
	jmp .Lhang
#set the size of _start to current location minus position of _start. 
.size _start, . - _start
