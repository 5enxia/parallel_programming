#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "timer.h"
#define NUM 10000

int main(int ac, char *av[])
{
    int n = NUM; //default
    double *a, *b, *c;
    if(ac > 1){
	n = atoi(av[1]);
	printf("n=%d\n", n);
    }
    a = new double [n];    b = new double [n];    c = new double [n];

    for(int i = 0; i < n; i++) { // Initialize a,b,c
	a[i] = i+1;
	b[i] = i+2;
        c[i] = 0;
    }

    double ts = dgettime();
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; ++j){
            c[i] += sin(a[i]/b[i]) + cos(b[i]/a[i]);
        }
    }
    double te = dgettime();
    printf("Time=%f\n", te-ts);

    delete [] a;    delete [] b;    delete [] c;
}
