#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>
#include "include/system.h"

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler. Exiting."
#endif

uint16_t keyboard_isEnter = 0;

unsigned char kbdus[128] =
{
  0,27,'1','2','3','4','5','6','7','8',	/* 9 */
  '9','0','-','=','\b',/* Backspace */
  '\t',	/* Tab */
  'q','w','e','r',/* 19 */
  't','y','u','i','o','p','[',']','\n',/* Enter key */
  0,/* 29   - Control */
  'a','s','d','f','g','h','j','k','l',';',/* 39 */
 '\'','`',0,/* Left shift */
 '\\','z','x','c','v','b','n',/* 49 */
  'm',',','.','/',0,/* Right shift */
  '*',
   0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

void keyboard_handler(struct regs *r)
{
	unsigned char scancode;
	//Read from port 60 when handler is called.
	//0x60 is the keyboard key port
	scancode = inportb(0x60);
	//if top bit is set, then key has just been released
	//useful for shifts and control/alt
	if (scancode & 0x80)
	{

	}
	else
	{
		terminal_putchar(kbdus[scancode]);
		if (kbdus[scancode] == '\n')
		{
			runShell();
		}
		//key just pressed down
	}
}
