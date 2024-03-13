#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef enum{
    FLAG_ERROR,
    OK
}status_code;



double avg_geom(int count, ...){
    double res, tmp;
    res = 0;
    int prod = 1;
    int n = count;
    va_list args;
    va_start(args, count);
    while (count > 0)
    {
        tmp = va_arg(args, double);
        prod *= tmp;
        count--;
    }
    va_end(args);
    res = pow(prod, 1. / n);
    return res;
}

double fast_pow(double base, int exp){
    if (exp == 0)
    {
        return 1;
    }
    else if (exp == 1)
    {
        return base;
    }
    else if (exp > 0)
    {
        return base * fast_pow(base, --exp);
    }
    else
    {
        return 1 / (base / fast_pow(base, ++exp));
    }
}

void msg(){
    puts("Я не отвечаю за кривые вводные данные");
    puts("Сначала введите основание потом показатель степени разделяя все это клавишей Enter");
}
int main(int argc, char** argv){
    printf("%.15f\n", avg_geom(5, 1.0, 3.0, 9.0, 27., 81.));
    printf("%.15f\n", avg_geom(5, 1.0, 4.0, .5, 14.78, 2.22));
    double base;
    int exp;
    msg();
    scanf("%lf", &base);
    scanf("%d", &exp);
    printf("%.15f\n", fast_pow(base, exp));
}