
/* mountain.c - Generate the memory mountain. */
/* $begin mountainmain */
#include <stdlib.h>
#include <stdio.h>
#include "clock.h" /* routines to get raw times */
#include "fcyc.h" /* measurement routines */

// typedef long data_t;
typedef long data_t;

#define MINBYTES (1 << 14)  /* First working set size */
#define MAXBYTES (1 << 27)  /* Last working set size */
#define MAXSTRIDE 15        /* Stride x8 bytes */
#define MAXELEMS MAXBYTES/sizeof(data_t) 


/* $begin mountainfuns */
data_t data[MAXELEMS];      /* The global array we'll be traversing */

/* $end mountainfuns */
/* $end mountainmain */
void init_data(data_t *data, long n);
void test(long *params);
double run(long size, long stride);

/* $begin mountainmain */
int main()
{
    long size;        /* Working set size (in bytes) */
    long stride;      /* Stride (in array elements) */

    init_data(data, MAXELEMS); /* Initialize each element in data */
/* $end mountainmain */
    /* Not shown in the text */
    printf("Memory mountain (MB/sec)\n");

    printf("\t");
    for (stride = 1; stride <= MAXSTRIDE; stride++)
	printf("s%ld\t", stride);
    printf("\n");

 /* $begin mountainmain */
    for (size = MAXBYTES; size >= MINBYTES; size >>= 1) {
/* $end mountainmain */
	/* Not shown in the text */
	if (size > (1 << 20))
	    printf("%ldm\t", size / (1 << 20));
	else
	    printf("%ldk\t", size / 1024);

/* $begin mountainmain */
	for (stride = 1; stride <= MAXSTRIDE; stride++) {
	    printf("%.0f\t", run(size, stride));
	    
	}
	printf("\n");
    }
    exit(0);
}
/* $end mountainmain */

/* init_data - initializes the array */
void init_data(data_t *data, long n)
{
    long i;

    for (i = 0; i < n; i++)
	data[i] = i;
}

volatile data_t accum = 0;

/* $begin mountainfuns */
/* test - Iterate over first "elems" elements of array "data" with
 *        stride of "stride", using 4x4 loop unrolling.
 */
void test(long *params)
{
    accum = 0;
    long elems = params[0];
    long stride = params[1];
    long i, sx2 = stride*2, sx3 = stride*3, sx4 = stride*4;
    data_t acc0 = 0, acc1 = 0, acc2 = 0, acc3 = 0;
    long length = elems;
    long limit = length - sx4;

    /* Combine 4 elements at a time */
    for (i = 0; i < limit; i += sx4) {
	acc0 = acc0 + data[i];     
        acc1 = acc1 + data[i+stride];
	acc2 = acc2 + data[i+sx2]; 
        acc3 = acc3 + data[i+sx3];
    }

    /* Finish any remaining elements */
    for (; i < length; i += stride) {
	acc0 = acc0 + data[i];
    }
    accum = ((acc0 + acc1) + (acc2 + acc3));
}

/* run - Run test({elems, stride}) and return read throughput (MB/s).
 *       "size" is in bytes, "stride" is in array elements
 */
double run(long size, long stride)
{   
    long elems = size / sizeof(data_t);
    long params[2] = {elems, stride};
    double secs;
    test(params);                     /* Warm up the cache */       //line:mem:warmup
    secs = fsec(test, params);        /* Call test({elems,stride}) */ //line:mem:fcyc
    return (size / stride) / (secs * 1e6); /* Convert secs to MB/s */  //line:mem:bwcompute
}
/* $end mountainfuns */


