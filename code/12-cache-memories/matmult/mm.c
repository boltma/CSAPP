/* matrix multiply permutations */
#include <stdio.h>
#include <stdlib.h>
#include "mm.h"
#include "fcyc.h"
#include "clock.h"

/* whether or not fcyc should clear the cache */
#define CLEARCACHE 0  

/* global arrays */
double ga[MAXN*MAXN], gb[MAXN*MAXN], gc[MAXN*MAXN]; 

#define USEN (n)

/* check the result array for correctness */
void checkresult(size_t n, double c[USEN][USEN])
{
    size_t i, j;

    for (i = 0; i < n; i++)
	for (j = 0; j < n; j++)
	    if (c[i][j] != (double)n) {
	      printf("Error: bad number (%f) in result matrix (%zd,%zd)\n", 
		       c[i][j], i, j);
	      fflush(stdout);
		exit(0);
	    }
}


/* Copy of function being measured */
static mmf_t mfun = NULL;

/* Function called to do time measurement */
void mm(long *params) {
    size_t n = params[0];
    mfun(n, (double (*)[USEN]) ga, (double (*)[USEN]) gb, (double (*)[USEN]) gc);
}

/* Run f and return clocks per inner loop iteration */
double run(mmf_t f, size_t n)
{
    double nspop;
    long params[1] = { n };
    set_fcyc_clear_cache(CLEARCACHE);
    set_fcyc_cache_size(1L << 23); /* 8MB */
    set_fcyc_cache_block(64);
    set_fcyc_min_reps(8);
    set_fcyc_min_ticks(1000);
    mfun = f;
    nspop = 1e9 * fsec(mm, params) / (2*n*n*n);
    checkresult(n, (double (*)[USEN]) gc);
    return(nspop);
}

/* reset result array to zero */
void reset(size_t n, double c[USEN][USEN])
{
    size_t i, j;
    
    for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++) {
	    c[i][j] = 0.0;
	}
    }
}

/* initialize input arrays to 1 */
void init(size_t n, double a[USEN][USEN], double b[USEN][USEN]) 
{
    size_t i, j;
    
    for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++) {
	    a[i][j] = 1.0;
	    b[i][j] = 1.0;
	}
    }
}


/* print an array (debug) */
void printarray(size_t n, double a[USEN][USEN])
{
    size_t i, j;

    for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++) {
	    printf("%5.1f ", a[i][j]);
	}
	printf("\n");
    }
}

/***********************************************
 * Six different versions of matrix multiply 
 ***********************************************/
void ijk(size_t n, double A[USEN][USEN], double B[USEN][USEN], double C[USEN][USEN]) 
{
    size_t i, j, k;
    double sum;

    /* $begin mm-ijk */
for (i = 0; i < n; i++) 
    for (j = 0; j < n; j++) {
	sum = 0.0;
	for (k = 0; k < n; k++)
	    sum += A[i][k]*B[k][j];
	C[i][j] = sum;
    }
/* $end mm-ijk */

}

void jik(size_t n, double A[USEN][USEN], double B[USEN][USEN], double C[USEN][USEN]) 
{
    size_t i, j, k;
    double sum;

/* $begin mm-jik */
for (j = 0; j < n; j++) 
    for (i = 0; i < n; i++) {
	sum = 0.0;
	for (k = 0; k < n; k++)
	    sum += A[i][k]*B[k][j];
	C[i][j] = sum;
    }
/* $end mm-jik */
}

void ikj(size_t n, double A[USEN][USEN], double B[USEN][USEN], double C[USEN][USEN]) 
{
    size_t i, j, k;
    double r;
    
    /* $begin mm-ikj */
    for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++)
	    C[i][j] = 0.0;
	for (k = 0; k < n; k++) {
	    r = A[i][k];
	    for (j = 0; j < n; j++)
		C[i][j] += r*B[k][j];
	}
    }
/* $end mm-ikj */
}

void kij(size_t n, double A[USEN][USEN], double B[USEN][USEN], double C[USEN][USEN])
{
    size_t i, j, k;
    double r;

    /* $begin mm-kij */
    for (i = 0; i < n; i++) 
	for (j = 0; j < n; j++)
	    C[i][j] = 0.0;
    for (k = 0; k < n; k++)
	for (i = 0; i < n; i++) {
	    r = A[i][k];
	    for (j = 0; j < n; j++)
		C[i][j] += r*B[k][j];
	}
/* $end mm-kij */
}

void kji(size_t n, double A[USEN][USEN], double B[USEN][USEN], double C[USEN][USEN])
{
    size_t i, j, k;
    double r;

    /* $begin mm-kji */
    for (i = 0; i < n; i++) 
	for (j = 0; j < n; j++)
	    C[i][j] = 0.0;
    for (k = 0; k < n; k++)
	for (j = 0; j < n; j++) {
	    r = B[k][j];
	    for (i = 0; i < n; i++)
		C[i][j] += A[i][k]*r;
	}
    /* $end mm-kji */
}

void jki(size_t n, double A[USEN][USEN], double B[USEN][USEN], double C[USEN][USEN])
{
    size_t i, j, k;
    double r;

/* $begin mm-jki */
    for (j = 0; j < n; j++) {
	for (i = 0; i < n; i++)
	    C[i][j] = 0.0;
	for (k = 0; k < n; k++) {
	    r = B[k][j];
	    for (i = 0; i < n; i++)
		C[i][j] += A[i][k]*r;
	}
    }
/* $end mm-jki */
}

/* 
 * Run the six versions of matrix multiply and display performance
 * as clock cycles per inner loop iteration.
 */ 

int main()
{
    int n;

    init(MAXN, (double (*)[MAXN]) ga, (double (*)[MAXN]) gb);

    printf("matmult ns/fp operation\n");
    printf("%3s%6s%6s%6s%6s%6s%6s\n", "n", 
	   "ijk", "jik", "jki", "kji", "kij", "ikj");
    fflush(stdout);
    for (n = MINN; n <= MAXN; n += INCN) {  
	printf("%3d ", n);

	printf("%5.2f ", run(ijk, n));
	printf("%5.2f ", run(jik, n));
	printf("%5.2f ", run(jki, n));
	printf("%5.2f ", run(kji, n));
	printf("%5.2f ", run(kij, n));
	printf("%5.2f ", run(ikj, n));
	printf("\n");
	fflush(stdout);
    }
    exit(0);
}

