#include <cstdio>
#include <cstdlib>
#include "timer.h"

int main(int ac, char *av[])
{
    int n = 10000;
    if(ac > 1){
	n = atoi(av[1]);
	printf("n=%d\n", n);
    }
    double step = 1.0/(double)n;
    double ds = step*step;
    double area = 0.0;
    double ts = dgettime();

    for(double x = step/2; x < 1.0; x+= step){
        for(double y = step/2; y < 1.0; y += step){
            double r = x * x + y * y;
            if(r <= 1.0) area += ds;
            else break;
        }
    }
    double te = dgettime();
    printf("PI=%f Time=%f\n", area*4, te-ts);

}

