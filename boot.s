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


.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp
	#mov %eax, %cr0
	#or %al, 1
	#mov %cr0, %eax
	call kernel_main
	cli
	hlt
.Lhang:
	jmp .Lhang
#set the size of _start to current location minus position of _start. 
.size _start, . - _start


# This will set up our new segment registers. We need to do
# something special in order to set CS. We do what is called a
# far jump. A jump that includes a segment as well as an offset.
# This is declared in C as 'extern void gdt_flush();'
.global gdt_flush    # Allows the C code to link to this
.extern gp           # Says that '_gp' is in another file
flush2: 
    ret
gdt_flush: 
    lgdt gp          # Load the GDT with our '_gp' which is a special pointer
    movw $0x10,%ax    # 0x10 is the offset in the GDT to our data segment
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%fs
    movw %ax,%gs
    movw %ax,%ss
    jmp $0x08,$flush2   # 0x08 is the offset to our code segment: Far jump!

#create the stack
.section .bss
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

