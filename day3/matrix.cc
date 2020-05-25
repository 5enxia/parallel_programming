#include <cstdio>
#include "timer.h"

#define N 1000
double a[N][N], b[N][N], c[N][N];
int main()
{
    int i, j, k;
    for (i=0; i<N; i++)
	for (j=0; j<N; j++){
	    a[i][j]= i+j;
	    b[i][j]= i*j;
	    c[i][j] = 0.0;
	}

    double st = dgettime();
    for(i=0;i<N;i++){
	for(j=0;j<N;j++){
	    for(k=0;k<N;k++) c[i][j] += a[i][k] * b[k][j];
	}
    }
    double et = dgettime();
    
    printf("Time =%f Sec Perf =%8.2f MFlops.\n", 
	   et-st, (double)N*N*N*2/((et-st)*1.0e6));
    return 0;
}

