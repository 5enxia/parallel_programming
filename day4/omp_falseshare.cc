#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include "timer.h"
#define NUM 100000
#define MAXTH 24
int main(int ac, char *av[])
{
    int n = NUM; //default
    int sum0[MAXTH*32] = {0};
    int sum1[MAXTH*32] = {0};
    int sum2[MAXTH*32] = {0};
    int sum3[MAXTH*32] = {0};
    int *data; // first address of array data[]
    double t[10];
    if(ac > 1){
	n = atoi(av[1]);
	printf("n=%d\n", n);
    }
    data = new int [n];
    for (int i = 0; i < n; i++) data[i] = i;
    t[0] = dgettime();
#pragma omp parallel
    {
	int id = omp_get_thread_num();
        for(int j = 0; j < 100; j++)
	for (int i = 0; i < n; i++){
	    sum0[id] += data[i];
	}
//        printf("sum %d = %d\n", id, sum0[id]);
    }
    t[1] = dgettime();
#pragma omp parallel
    {
	int id = omp_get_thread_num();
        for(int j = 0; j < 100; j++)
	for (int i = 0; i < n; i++){
	    sum1[id*32] += data[i];
	}
//        printf("sum %d = %d\n", id, sum1[id*32]);
    }
    t[2] = dgettime();
#pragma omp parallel
    {
	int id = omp_get_thread_num();
        for(int j = 0; j < 100; j++)
	for (int i = 0; i < n; i++){
#pragma omp atomic	    
	    sum2[id] += data[i];
	}
//        printf("sum %d = %d\n", id, sum1[id*32]);
    }
    t[3] = dgettime();
#pragma omp parallel
    {
	int id = omp_get_thread_num();
        for(int j = 0; j < 100; j++)
	for (int i = 0; i < n; i++){
#pragma omp atomic	    
	    sum3[id*32] += data[i];
	}
//        printf("sum %d = %d\n", id, sum1[id*32]);
    }
    t[4] = dgettime();
    printf("Time %f %f %f %f\n", 
	   t[1]-t[0], t[2]-t[1], t[3]-t[2],t[4]-t[3]);
}

