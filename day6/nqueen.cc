#include <cstdio>
#include <cstdlib>
#include "timer.h"

#define N  20  // max n

char a[N], b[2 * N - 1], c[2 * N - 1], x[N];
int n = 8;
int solution = 0;
int debug = 0;
void found(void)
{
    ++solution;
    if(debug){
	printf("\nsolution %d\n", solution);
	for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (x[i] == j) printf(" Q");
                else           printf(" .");
            }
            printf("\n");
	}
    }
}

void placequeen(int i)
{
    for (int j = 0; j < n; j++) {
        if (a[j] && b[i+j] && c[i-j+n-1]) {
            x[i] = j;
            a[j] = b[i+j] = c[i-j+n-1] = 0;
            if (i < n - 1) placequeen(i + 1);
            else found();
            a[j] = b[i+j] = c[i-j+n-1] = 1;
        }
    }
}

int main(int ac, char *av[])
{
    int i;
    if(ac > 1) n = atoi(av[1]);
    if(n < 0) {
        n = -n;
        debug = 1;
    }
    for (i = 0; i < n; i++)         a[i] = 1;
    for (i = 0; i < 2 * n - 1; i++) b[i] = 1;
    for (i = 0; i < 2 * n - 1; i++) c[i] = 1;
    double ts = dgettime();
    placequeen(0);
    double te = dgettime();
    printf("Number of solution %d Time=%f\n", solution, te-ts);
    return 0;
}
