#include <cstdio>
#include <cstdlib>
void bsort(int *a, int n) {
    for(int i = n - 1; i > 0; --i){
	for(int j = 0; j < i; ++j){
	    if(a[j] > a[j+1]){
		int temp = a[j]; a[j] = a[j+1]; a[j+1] = temp;
	    }
	}
    }
}
int main(int ac, char *av[]) {
    int n = 10;
    if(ac > 1){ n = atoi(av[1]);   }
    int *ia = new int [n];
    for(int i = 0; i < n; i++){
	ia[i] = random();
    }
    bsort(ia, n);
    for(int i = 0; i < n-1; i++){// Error check
	if(ia[i] > ia[i+1]) printf("Error %d %d %d\n", i, ia[i], ia[i+1]);
    }
    delete [] ia;
    return 0;
}

