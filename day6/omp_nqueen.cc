#include <cstdio>
#include <cstdlib>
#include "timer.h"
#ifdef _OPENMP
#include <omp.h>
#endif

#define N  20  // max n
#define MAXTASK 10000

char a[MAXTASK][N], b[MAXTASK][2 * N - 1];
char c[MAXTASK][2 * N - 1], x[MAXTASK][N];
char ia[N], ib[2 * N - 1], ic[2 * N - 1], ix[N];
int numtask = 0;
int n = 8;

int solution = 0;
int debug = 0;
void printboard(int tid)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j){
            if (x[tid][i] == j) printf(" Q");
            else           printf(" .");
        }
        printf("\n");
    }
}
void found(int tid)
{
    ++solution;
    if(debug) {
	printf("\nsolution %d\n", solution);
        printboard(tid);
    }
}

void placequeen(int i, int tid)
{
    for (int j = 0; j < n; ++j) {
        if (a[tid][j] && b[tid][i + j] && c[tid][i - j + n - 1]) {
            x[tid][i] = j;
            if (i < n - 1) {
                a[tid][j] = b[tid][i + j] = c[tid][i - j + n - 1] = 0;
                placequeen(i + 1, tid);
                a[tid][j] = b[tid][i + j] = c[tid][i - j + n - 1] = 1;
            } else found(tid);
        }
    }
}
void copydata(int tid)
{
    for (int i = 0; i < n; ++i){
            a[tid][i] = ia[i];
            x[tid][i] = ix[i];
        }
    for (int i = 0; i < 2 * n - 1; ++i) b[tid][i] = ib[i];
    for (int i = 0; i < 2 * n - 1; ++i) c[tid][i] = ic[i];
}

void maketask(int i, int level)
{
    for (int j = 0; j < n; ++j) {
        if (ia[j] && ib[i + j] && ic[i - j + n - 1]) {
            ix[i] = j;
            ia[j] = ib[i + j] = ic[i - j + n - 1] = 0;
            if (i < level-1) {
                maketask(i + 1, level);

            } else {
                copydata(numtask);
                ++numtask;
                if(numtask >= MAXTASK){
                    printf("Too many task\n");
                    exit(1);
                }
            }
            ia[j] = ib[i + j] = ic[i - j + n - 1] = 1;
        }
    }
}

int main(int ac, char *av[])
{
    if(ac > 1) n = atoi(av[1]);
    if(n < 0) {
        n = -n;
        debug = 1;
    }
    int level = 2;
    if(ac > 2) level = atoi(av[2]);

    for (int i = 0; i < n; ++i){
        ia[i] = 1;
        ix[i] = -1;
    }
    for (int i = 0; i < 2 * n - 1; ++i) ib[i] = 1;
    for (int i = 0; i < 2 * n - 1; ++i) ic[i] = 1;
    printf("Num Procs %d\n", omp_get_num_procs());

    double ts = dgettime();
    maketask(0, level);
    if(debug){
        for(int i = 0; i < numtask; ++i){
            printf("\nPlacement %d\n", i);
            printboard(i);
        }
    }
    printf("Numtask = %d level=%d\n", numtask, level);

    double tm = dgettime();

    for(int i = 0; i < numtask; ++i){
        placequeen(level, i);
    }
    double te = dgettime();
    printf("Number of solution %d Make Time=%f Search Time%f Total Time=%f\n", 
           solution, tm-ts, te-tm, te-ts);
    return 0;
}
