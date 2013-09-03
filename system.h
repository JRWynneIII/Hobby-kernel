#ifndef SYSTEM_H_
#define SYSTEM_H_

void outportb (unsigned short _port, unsigned char _data);

void *memcpy(void *dest, const void *src, size_t count);

//unsigned char *memset(unsigned char *dest, unsigned char val, int count);
void *memset(void *dest, char val, size_t count);

//unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);

size_t strlen(const char* str);

unsigned char inportb (unsigned short _port);

void gdt_install();

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

#endif
