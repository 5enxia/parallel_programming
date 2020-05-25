#include <cstdio>
#include <omp.h>

int main(){
  int np = omp_get_num_procs();
  int id = omp_get_thread_num();
  int nt = omp_get_num_threads();
  printf("Begin nproc=%d Thred %d Num thread %d\n", np, id, nt);

  #pragma omp parallel private(id, nt)
  {
    id = omp_get_thread_num();
    nt = omp_get_num_threads();
    printf("Hello World from Thread %d Num thread=%d\n", id, nt);
  }

  id = omp_get_thread_num();
  nt = omp_get_num_threads();
  printf("Bye Thread %d Num thread %d\n", id, nt);
  return 0;
}

