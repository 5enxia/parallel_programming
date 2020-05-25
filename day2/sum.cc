#include <cstdio>
#include <cstdlib>
#define NUM 100000
int main(int ac, char *av[]){
    int n = NUM; //default
    double *data; // first address of array data[]
    if(ac > 1){
	n = atoi(av[1]);
    }
    data = new double [n];

    for (int i = 0; i < n; i++) data[i] = i;
    double sum = 0;
    for (int i = 0; i < n; i++){
	sum += data[i];
    }
    printf("n=%d sum = %f\n", n, sum);
}

