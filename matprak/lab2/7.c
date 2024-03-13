#include <stdio.h>
#include <math.h>

double ex1(double x){
    return sin(x) / x * x;
}

double ex2(double x){
    return (2.5 * x) - 1;
}
double dich_root(double a, double b, double eps, double (*func)(double)){
    double c;
    while (fabs(b - a) > eps)
    {
        c = (a + b) / 2;
        if (func(b) * func(c) < 0)
        {
            a = c;
        }
        else
        {
            b = c;
        }
    }
    return (a + b) / 2;
}
int main(){
    printf("%.39f\n", dich_root(-4., -3., .0000000000001, ex1));
    printf("%.39f\n", dich_root(.0, 1., .0000000000001, ex2));
}