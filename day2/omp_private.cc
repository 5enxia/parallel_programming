#include <cstdio>
#include <omp.h>

int main(){
    int i;
    int t;
    int a[10];
    t = -100;
    printf("private t = %d\n", t);
#pragma omp parallel for private(t)
    for(i = 0; i < 10; i++) {
      t = 1;
	a[i] = t;
	printf("%d ", a[i]);
    } 
    printf("\nafter private t = %d\n", t);

    t = -100;
    printf("firstprivate t = %d\n", t);
#pragma omp parallel for firstprivate(t)
    for(i = 0; i < 10; i++) {
	a[i] =t*i;
	printf("%d ", a[i]);
    } 
    printf("\nafter firstprivate t = %d\n", t);

    t = -100;
    printf("lastprivate t = %d\n", t);
#pragma omp parallel for lastprivate(t)
    for(i = 0; i < 10; i++) {
	t= i;
	a[i] = t;
	printf("%d ", a[i]);
    } 
    printf("\nafter lastprivate t = %d\n", t);

    t = -100;
    printf("reduction t = %d\n", t);
#pragma omp parallel for reduction(+:t)
    for(i = 0; i < 10; i++) {
	printf("%d ", a[i]);
	t += a[i];
    }
    printf("\nafter reduction t= %d\n", t);
}
