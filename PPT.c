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

#define CEILING(x,y) (((x) + (y) - 1) / (y))
#define LOOPS CEILING(TARGET-1,3)

number_t queue[MAX_QUEUE];

unsigned short tail = 0;
unsigned short head = 0;

unsigned short count = 0;


#define enqueue(item) \
queue[tail++] = (item)

#define dequeue() \
queue[head++]


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
	number_t a,b,c;
	number_t a1,b1;
	number_t a2;
	number_t da, db, dc, tc;
	number_t s;	
	
	a = dequeue();
	b = dequeue();
	c = dequeue();

	da = a<<1;
	db = b<<1;
	dc = c<<1;
	tc = dc+c;
	s = db+tc;

	a1 = a-db+dc; 
	a2 = a1 + (db<<1);	
	b1 = da-b+dc; 
	
	enqueue(a1); // a1
	enqueue(b1); // b1
	enqueue(da-db+tc); // c1
	
	enqueue(a2); // a2
	enqueue(b1+db); // b2
	enqueue(da+s); // c2
	
	enqueue(a2-da); // a3
	enqueue((dc<<1)-b1); // b3
	enqueue(s-da); // c3	
}


int main(void)
{
    clock_t Ticks;
    unsigned int Sec;
    unsigned int Milli;
    
    enqueue(3);
    enqueue(4);
    enqueue(5);
    count = 0;
    printf("Press enter to start\n");
    getchar();
    printf("\nComputing...\n");
    
    Ticks = clock();

    while(++count<=LOOPS)
    {
		compute_new_triples();
    }

    Ticks = clock() - Ticks;
    Sec = (unsigned) (Ticks / CLOCKS_PER_SEC);
    Milli = ((Ticks % CLOCKS_PER_SEC) * 1000) / CLOCKS_PER_SEC;
    printf ("Time used: %u.%03u seconds\n", Sec, Milli);    
    
    printf("Press enter to print the triples\n");
    getchar();
    display_triples(DISPLAY_START,TARGET);
    return 0;
}
