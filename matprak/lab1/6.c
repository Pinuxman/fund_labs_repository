#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef enum{
    OK,
    INVALID_INPUT,
    WRONG_FORMAT
}status_code;

status_code double_number_checker(char *s){
    int len = strlen(s);
    if (len > 1){
        for (int i = 0; i < len; ++i) {
            if ((s[i] < '0' || s[i] > '9') && s[i] != '.'){
                return INVALID_INPUT;
            }
        }
        return OK;
    }
    else{
        if (s[0] < '0' || s[0] > '9'){
            return INVALID_INPUT;
        }
        return OK;
    }
}

double a_func(double x){
    if (x == 0)
    {
        return .43; 
    }
    return log(1 + x) / x;
}
double b_func(double x){
    return pow(M_E, -x*x/2);
}
double c_func(double x){
    if (x >= 1) 
    {
        return 2; 
    }
    return log(1/(1 - x));
}
double d_func(double x){
    return pow(x, x);
}

double integral_calc(double (*func)(double), double eps, const char* side){
    double bounds[2] = {0., 1.};
    double res = 0.;
    double prev;
    double acc = 2.;
    do
    {
        double step = (bounds[1] - bounds[0]) / acc;
        prev = res;
        res = 0;
        if (strcmp(side, "left"))
        {
            for (double cur = bounds[1]; cur > bounds[0] + eps; cur -= step)
            {
                res += step * func(cur);
            }
        }
        else if(strcmp(side, "right"))
        {
            for (double cur = bounds[0]; cur < bounds[1] - eps; cur += step)
            {
                res += step * func(cur);
            }
        }
    }while (fabs(prev - res) > eps);
    return res;
}

status_code validator(int argc, char **argv){
    if (argc != 2){
        printf("Wrong format!\n");
        return WRONG_FORMAT;
    }
    if(double_number_checker(argv[1]) == INVALID_INPUT){
        printf("Not a number given!\n");
        return INVALID_INPUT;
    }
    return OK;
}

void print_integral_result(double eps){
    printf("a. %.16f\n", integral_calc(a_func, eps, "left"));
    printf("b. %.16f\n", integral_calc(b_func, eps, "left"));
    printf("c. %.16f\n", integral_calc(c_func, eps, "right"));
    printf("d. %.16f\n", integral_calc(d_func, eps, "left"));
}

void status(status_code flag){
    switch (flag) {
        case INVALID_INPUT:
            printf("Not a number given!\n"); break;
        case WRONG_FORMAT:
            printf("Wrong format!\n"); break;
        case OK:
            printf("Done!\n"); break;
    }
}

int main(int argc, char** argv){
    if(validator(argc, argv) == OK)
    {
        print_integral_result(strtod(argv[1], NULL));
    }
    else{
        status(validator(argc, argv));
    }
}