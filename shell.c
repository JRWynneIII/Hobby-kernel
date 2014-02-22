#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>
#include "include/system.h"

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler. Exiting."
#endif

void init_shell()
{
	tcputs("Welcome to Polaris\n\n", COLOR_WHITE);
	tcputs("$>> ", COLOR_GREEN);
	//tputs(1/0);
}
