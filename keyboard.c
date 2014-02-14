#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"
#include "system.h"

#if defined(__linux__)
#error "You are not using a cross-compiler. Exiting."
#endif

typedef struct keyQueue
{
	size_t outQueue[15];
	size_t newPress;
	size_t bottomOfStack;
};

keyQueue queue;
queue.bottomOfStack = queue.outQueue[0];

void init_keyboard()
{
	memset(queue.outQueue, 0, 15);

}

void init_PIC()
{
	//PIC1 Command: 0x20	data: 0x21
	//PIC2 Command: 0xA0	data: 0xA1
	//
	//0x11 = initialize command
	//	makes PIC wait for 3 more words
	//
	
}

void queuePush(size_t code)
{
	size_t i = 0;
	for (i = 0; i<15; i++)
	{
		if (queue.outQueue[i] == 0)
			break;
	}
	queue.outQueue[i] = queue.newPress;
}

void keyPressed(size_t code)
{
	queue.newPress = code;
}
