#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>
#include "vga.h"
#include "system.h"

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
void kernel_main()
{
	terminal_initialize();
	tcputs("Welcome to PolarisOS\n", COLOR_WHITE);
	tcputs("Prompt$ ", COLOR_GREEN);
	cls();
	tputs("hello");
	for (;;);
}
