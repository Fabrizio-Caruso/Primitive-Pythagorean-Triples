#include <stdio.h>
#include <time.h>

#if !defined(TARGET)
	#define TARGET 1000
#endif


#if !defined(DISPLAY_START)
	#define DISPLAY_START 981
#endif

#if defined(USE_SHORT)
	typedef unsigned short number_t;
	#define DISPLAY_STRING "%u: %u %u %u\n"
#else
	typedef unsigned long number_t; 
	#define DISPLAY_STRING "%u: %lu %lu %lu\n"
#endif
#define SIZE_T sizeof(number_t)
#define TRIPLES_PER_LOOP 12
#define MAX_QUEUE (TARGET*SIZE_T+TRIPLES_PER_LOOP-1) 


#define CEILING(x,y) (((x) + (y) - 1) / (y))
#define LOOPS CEILING(TARGET-1,TRIPLES_PER_LOOP)

number_t queue[MAX_QUEUE];

#if defined(EXTERN_VARS)
	#include "extern_long_vars.h"
#else
	unsigned short count = 0;
	number_t *tail;
	number_t *head;

	number_t a,b,c;
	number_t a1,b1;
	number_t a2;
	number_t aa1,aa2,aa3;
	number_t ab1,ab2,ab3;
	number_t ac1,ac2,ac3;
	number_t ba1,ba2,ba3;
	number_t bb1,bb2,bb3;
	number_t bc1,bc2,bc3;
	number_t ca1,ca2,ca3;
	number_t cb1,cb2,cb3;
	number_t cc1,cc2,cc3;
	number_t a_2, b_2, c_2, a_3, b_3, c_3, a_7, b_7;
	number_t a_4,b_4,c_4,a_8,b_8,c_8;
	number_t a_9,b_9,c_9,a_12,b_12,c_12,c_17;
	number_t s;	
#endif



#define enqueue(item) \
	*(tail++) = (number_t)(item)

#define dequeue() \
	(number_t) *(head++)


void display_triples(number_t start_index, number_t end_index)
{
    unsigned short i;
    
	printf("\n");
    for(i=start_index-1;i<end_index;++i)
    {
        printf(DISPLAY_STRING, i+1, queue[3*i], queue[3*i+1],queue[3*i+2]);
    }
    printf("\n");
}


void compute_new_triples(void)
{
	a = dequeue();
	b = dequeue();
	c = dequeue();

	a_2 = a<<1;
	b_2 = b<<1;
	c_2 = c<<1;
	c_3 = c_2+c;
	s = b_2+c_3;

	a1 = a-b_2+c_2; 
	a2 = a1 + (b_2<<1);	
	b1 = a_2-b+c_2; 
	
	enqueue(a1); // a1
	enqueue(b1); // b1
	enqueue(a_2+c_3-b_2); // c1
	
	enqueue(a2); // a2
	enqueue(b1+b_2); // b2
	enqueue(a_2+s); // c2
	
	enqueue(a2-a_2); // a3
	enqueue((c_2<<1)-b1); // b3
	enqueue(s-a_2); // c3	
	
	head+=9;
	
	a_4 = a_2<<1;
	a_8 = a_4<<1;
	a_3 = a_2+a;
	b_3 = b_2+b;

	b_4 = b_2<<1;
	b_8 = b_4<<1;
	c_4 = c_2<<1;
	c_8 = c_4<<1;

	a_7 = a_4+a_3;
	b_7 = b_4+b_3;	
	
	a_9 = a_8+a;
	b_9 = b_8+b;
	c_9 = c_8+c;
	
	a_12 = a_3<<2;
	b_12 = b_3<<2;
	c_12 = c_3<<2;
	
	c_17 = c+(c_4<<2);
	
	
/*
	number_t a_2, b_2, c_2, c_3, a_7, b_7;
	number_t a_4,b_4,c_4,a_8,b_8,c_8;
	number_t a_9,b_9,c_9,a_12,b_12,c_12,c_17;
a2:matrix([1, - 4, 4], [4, - 7, 8], [4, - 8, 9]);
ab:matrix([1, 4, 4], [4, 7, 8], [4, 8, 9]);
ac:matrix([- 1, 4, 4], [- 4, 7, 8], [- 4, 8, 9]);
ba:matrix([9, - 8, 12], [8, - 9, 12], [12, - 12, 17]);
b2:matrix([9, 8, 12], [8, 9, 12], [12, 12, 17]);
bc:matrix([- 9, 8, 12], [- 8, 9, 12], [- 12, 12, 17]);
ca:matrix([7, - 4, 8], [4, - 1, 4], [8, - 4, 9]);
cb:matrix([7, 4, 8], [4, 1, 4], [8, 4, 9]);
c2:matrix([- 7, 4, 8], [- 4, 1, 4], [- 8, 4, 9]);
*/	
	aa1 = a   + c_4 - b_4;
	aa2 = a_4 + c_8 - b_7;
	aa3 = a_4 + c_9 - b_8;
	ab1 = a   + b_4 + c_4;
	ab2 = a_4 + b_7 + c_8;
	ab3 = a_4 + b_8 + c_9;
	ac1 = b_4 + c_4 - a;
	ac2 = b_7 + c_8 - a_4;
	ac3 = b_8 + c_9 - a_4;
	ba1 = a_9  + c_12 - b_8;
	ba2 = a_8  + c_12 - b_9;
	ba3 = a_12 + c_17 - b_12;
	bb1 = a_9  + b_8  + c_12;
	bb2 = a_8  + b_9  + c_12;
	bb3 = a_12 + b_12 + c_17;
	bc1 = b_8  + c_12 - a_9;
	bc2 = b_9  + c_12 - a_8;
	bc3 = b_12 + c_17 - a_12;
	ca1 = a_7  + c_8 - b_4;
	ca2 = a_4  + c_4 - b;
	ca3 = a_8  + c_9 - b_4;
	cb1 = a_7  + b_4 + c_8;
	cb2 = a_4  + b   + c_4;
	cb3 = a_8  + b_4 + c_9;
	cc1 = b_4  + c_8 - a_7;
	cc2 = b    + c_4 - a_4;
	cc3 = b_4  + c_9 - a_8;
	
	enqueue(aa1);enqueue(aa2);enqueue(aa3); // 1
	enqueue(ba1);enqueue(ba2);enqueue(ba3); // 2
	enqueue(ca1);enqueue(ca2);enqueue(ca3); // 3
	enqueue(ab1);enqueue(ab2);enqueue(ab3); // 4
	enqueue(bb1);enqueue(bb2);enqueue(bb3); // 5
	enqueue(cb1);enqueue(cb2);enqueue(cb3); // 6	
	enqueue(ac1);enqueue(ac2);enqueue(ac3); // 7
	enqueue(bc1);enqueue(bc2);enqueue(bc3); // 8
	enqueue(cc1);enqueue(cc2);enqueue(cc3);	// 9
}


int main(void)
{
    clock_t Ticks, TicksDelta;
    unsigned int Sec;
    unsigned int Milli;
	
	head = tail = queue;
    
    enqueue(3);
    enqueue(4);
    enqueue(5);

    printf("Press enter to start\n");
    getchar();
	printf("\nLoops: %u\n", LOOPS); 
    printf("\nComputing...\n");
    
    Ticks = clock();

    while(++count<=LOOPS)
    {
		compute_new_triples();
    }

    TicksDelta = clock() - Ticks;
    Sec = (unsigned short) (TicksDelta / CLOCKS_PER_SEC);
    Milli = ((TicksDelta % CLOCKS_PER_SEC) * 1000) / CLOCKS_PER_SEC;
    printf ("Time used: %u.%03u seconds = %u ticks\n", Sec, Milli, (unsigned short) TicksDelta);    
    
    printf("Press enter to print the triples\n");
    getchar();
    display_triples(DISPLAY_START,TARGET);
    return 0;
}
