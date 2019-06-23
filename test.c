#include <stdio.h>
unsigned short queue[5000];
unsigned short a,b;
unsigned short *head;
unsigned short *tail;
int main(void)
{
    head = queue;
	tail = queue;
    *(tail++) = (unsigned short) 3;
	*(tail++) = (unsigned short) 4;
	a = (unsigned short) *(head++);
	b = (unsigned short) *(head++);
	printf("a: %u\n",a);
	printf("b: %u\n",b);
    return 0;
}
