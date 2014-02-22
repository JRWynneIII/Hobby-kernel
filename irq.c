#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "include/system.h"
#define PIC_READ_IRR 0x0a	//Raised IRQ
#define PIC_READ_ISR 0x0b
#define PIC1_COMMAND 0x20
#define PIC2_COMMAND 0xA0
#define PIC1_DATA 0x21
#define PIC2_DATA 0xA1
#define PIC_INIT 0x11

#if defined(__linux__)
#error "You are not using a cross-compiler. Exiting."
#endif

void irq_handler()
{
}


void PICsendEOI(unsigned char irq)
{
	//must send 0x20 (EOI) to BOTH PICs if the IRQ came from the slave PIC (0xA0)
	if (irq>=8)
		outportb(0xA0, 0x20);
	outportb(0x20, 0x20);
}


void init_PIC()
{
	//PIC1 Command: 0x20	data: 0x21
	//PIC2 Command: 0xA0	data: 0xA1
	//Send a 0x20 to the Command Port for EOI
	//
	//0x11 = initialize command
	//	makes PIC wait for 3 more words
	//	fist: vector offset
	//	second: how it is wired to slave/master
	//	third: environment info
	


	//Save the PIC masks
	unsigned char mask1, mask2;
	mask1 = inportb(PIC1_DATA);
	mask2 = inportb(PIC2_DATA);

	//initialize the PICs
	outportb(PIC1_COMMAND, PIC_INIT);
	io_wait();
	outportb(PIC2_COMMAND, PIC_INIT);
	io_wait();
	//set vector table offset!!
	outportb(PIC1_DATA, 32);
	io_wait();
	outportb(PIC2_DATA, 40);
	io_wait();
	//tell master there is a slave at irq2
	outportb(PIC1_DATA, 4);
	io_wait();
	//tell slave its cascade identity??	
	outportb(PIC2_DATA, 2);
	io_wait();
	//put PICs into 8086 mode 
	outportb(PIC1_DATA, 0x01);
	io_wait();
	outportb(PIC2_DATA, 0x01);
	io_wait();
	//restore the saved masks
	outportb(PIC1_DATA, mask1);
	outportb(PIC2_DATA, mask2);

	
}

void install_irq()
{
	init_PIC();
}
