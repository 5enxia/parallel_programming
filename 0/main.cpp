#include <omp.h>
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int np = omp_get_num_procs();
    int id = omp_get_thread_num();
    int nt = omp_get_num_threads();
    printf("Begin nproc = %d ",np);
    printf("Thread %d ", id);
    printf("Num thread %d\n", nt);

    #pragma omp parallel private(id, nt)
    {
        id = omp_get_thread_num();
        nt = omp_get_num_threads();
        printf("Hello World from Thread %d ", id); 
        printf("Num thread= %d\n", nt); 
    } 
    id = omp_get_thread_num();
    nt = omp_get_num_threads();
    printf("Bye Thread %d ", id);
    printf("Num thread %d\n", nt);
    return 0;
}


