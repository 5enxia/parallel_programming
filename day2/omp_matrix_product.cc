#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <iostream>
#include <vector>

#include <omp.h>

#include "timer.h"

using namespace std;

int main(int argc, char const *argv[])
{
    // INIT
    int N = 1000;
    if(argc == 2) N = atoi(argv[1]);
    vector<double> A(N*N), B(N*N), C(N*N);
    
    
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int index = i * N + j;
                A[index]= i + j; B[index]= i * j; C[index]= 0.0;
            }
        }
    }

    // START CALC
    double start = dgettime();

    // MATRIX PRODUCT
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int index = i * N + j;
                C[index] = A[index] * B[index];
            }
        }
    }

    // END CALC
    double end = dgettime();
    double elapsed = end - start;

    printf("Time =%f Sec Perf =%8.2f MFlops.\n",elapsed,2*pow(N,3)/(elapsed*1e6));
    
    A.clear(); B.clear(); C.clear();
    return 0;
}
