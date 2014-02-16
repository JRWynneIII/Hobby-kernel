#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>
#include "include/vga.h"
#include "include/keyboard.h"
#include "include/system.h"

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler. Exiting."
#endif
 
void kernel_main()
{
	gdt_install();
	idt_install();
	isrs_install();
	terminal_initialize();
	init_keyboard();
	tcputs("Welcome to Polaris\n\n", COLOR_WHITE);
	tcputs("$>> ", COLOR_GREEN);
	for (;;);
}
