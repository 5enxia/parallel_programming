#include <cstdio>
#include <cstdlib>
#define NUM 1000

int main(int ac, char *av[])
{
    int n = NUM; //default
    int *a, *b, *c; // first address of array a,b,c 
    if(ac > 1){
	n = atoi(av[1]);
	printf("n=%d\n", n);
    }
    a = new int [n];    b = new int [n];    c = new int [n];
    for(int i = 0; i < n; i++) { // Initialize a,b
      a[i] = i;	  b[i] = i*i;
    }
    for(int i = 0; i < n; i++){ // Compute c
      c[i] = a[i] + b[i];
    }
    delete [] a;    delete [] b;    delete [] c;
}

