#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define N 10000000

int main(int ac, char *av[])
{
    int n = N;
    if(ac > 1){
	n = atoi(av[1]);
	printf("n=%d\n", n);
    }
    int nv2 = 0;
    double ts = dgettime();
    for(int i = 0; i < n; i++){
	double x = (double)random() / (double)(RAND_MAX);
	double y = (double)random() / (double)(RAND_MAX);
	double v2 = x * x + y * y;
	if(v2 <= 1.0) nv2++;
    }
    double area = (double)nv2/(double)n;
    double te = dgettime();
    printf("PI=%f Time=%f\n", area*4, te-ts);
    return 0;
}
