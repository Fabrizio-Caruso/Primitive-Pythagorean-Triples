#include <stdio.h>
#include <time.h>

#define MAX_QUEUE 0x0FFF
#if !defined(TARGET)
	#define TARGET 1000
#endif

#define MAX_QUEUE 0x0FFF
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

number_t queue[MAX_QUEUE];


#if defined(EXTERN_VARS)
	#include "extern_short_vars.h"
#else
	unsigned short count = 0;
	number_t *tail;
	number_t *head;

	number_t a,b,c;
	number_t a1,b1,c1;
	number_t a2;
	number_t a3,b3,c3;
	number_t da, db, dc, tc;
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

void compute_new_triplets(void)
{
	a = dequeue();
	b = dequeue();
	c = dequeue();

	da = a<<1;
	db = b<<1;
	dc = c<<1;
	tc = dc+c;
	s = db+tc;

	a1 = a-db+dc; 
	a2 = a+db+dc;
	a3 = a2-da;
	b1 = da+dc-b; 
	b3 = (dc<<1)-b1;
	c1 = da+tc-db;
	c3 = s-da;

	enqueue(a1); enqueue(b1); enqueue(c1);
	enqueue(a2); enqueue(b1+db); enqueue(da+s);
	enqueue(a3); enqueue(b3); enqueue(c3);
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
    count = 1;
    printf("Press enter to start\n");
    getchar();
    printf("\nComputing...\n");
    
    Ticks = clock();

    while(count<TARGET)
    {
        compute_new_triplets();
        count+=3;
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
