all: boot.o kernel.o clean
	i586-elf-as boot.s -o boot.o
	i586-elf-gcc -c idt.c -o idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i586-elf-gcc -c keyboard.c -o keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i586-elf-gcc -c isrs.c -o isrs.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i586-elf-gcc -c kernel.c -o k.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i586-elf-gcc -c gdt.c -o gdt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i586-elf-gcc -c vga.c -o v.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i586-elf-gcc -c system.c -o sys.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i586-elf-gcc -T linker.ld -o os.bin -ffreestanding -O2 -nostdlib isrs.o gdt.o boot.o k.o v.o keyboard.o idt.o sys.o -lgcc
	cp os.bin isodir/boot/
	grub-mkrescue -o os.iso isodir
	qemu-system-i386 -vga cirrus -cdrom os.iso
	rm os.bin *.o
boot.o:
	i586-elf-as  boot.s -o boot.o
kernel.o:
	i586-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

clean:
	rm -f *.o
