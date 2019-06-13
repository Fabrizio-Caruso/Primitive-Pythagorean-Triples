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
    
    for(i=start_index-1;i<end_index;++i)
    {
        printf(DISPLAY_STRING, i+1, queue[3*i], queue[3*i+1],queue[3*i+2]);
    }
    printf("\n");
}

void compute_new_triplets(void)
{
number_t a,b,c;
number_t a1,b1,c1;
number_t a2,b2,c2;
number_t a3,b3,c3;
number_t da, db, dc, tc;

a = dequeue();
b = dequeue();
c = dequeue();

da = a<<1;
db = b<<1;
dc = c<<1;
tc = dc+c;

// Alternative
// a1 = da+b-c; a2 = a1+dc; a3 = a2-db;
// b1 = -da+db+dc; b2 = da-db+dc; b3 = da+db+dc;
// c1 = -da+b+tc; c2 = da-b+tc; c3 = c2+db;

a1 = a-db+dc; a2 = a+db+dc; a3 = a2-da;
b1 = da-b+dc; b2 = b1+db; b3 = -da+b+dc;
c1 = da-db+tc; c2 = da+db+tc; c3 = -da+db+tc;

enqueue(a1); enqueue(b1); enqueue(c1);
enqueue(a2); enqueue(b2); enqueue(c2);
enqueue(a3); enqueue(b3); enqueue(c3);
}

int main(void)
{
    clock_t Ticks;
    unsigned Sec;
    unsigned Milli;
    
    enqueue(3);
    enqueue(4);
    enqueue(5);
    count = 1;
    printf("Press enter to start\n");
    getchar();
    printf("Computing...\n");
    
    Ticks = clock();

    while(count<TARGET)
    {
        compute_new_triplets();
        count+=3;
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
