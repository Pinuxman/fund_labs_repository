#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef enum
{
    OK,
    INVALID_INPUT
}status_code;

void usage(){
    puts("Данная программа вычисляет суммы с заданой точностью");
    puts("Ввод: ε, x");
}

status_code is_number(char s[]){
    int cnt = 0;
    if (s[0] != '-')
    {
        for (int i = 0; i < strlen(s); i++)
        {
            if (s[i] == '.')
            {
                cnt++;
            }
            if (s[i] != '.')
            {
                if (!isdigit(s[i]))
                {
                    return INVALID_INPUT;
                }
            }
            if (cnt > 1)
            {
                return INVALID_INPUT;
            }
        }
        
    }

    else
    {
        for (int i = 1; i < strlen(s); i++)
        {
            if (s[i] == '.')
            {
                cnt++;
            }
            if (s[i] != '.')
            {
                if (!isdigit(s[i]))
                {
                    return INVALID_INPUT;
                }
            }
            if (cnt > 1)
            {
                return INVALID_INPUT;
            }
        }
        
    }
    return OK;
}

status_code validator(int argc, char** argv){

    if (argc != 3)
    {
        return INVALID_INPUT;
    }
    
    if (is_number(argv[1]) == INVALID_INPUT || is_number(argv[2]) == INVALID_INPUT)
    {
        return INVALID_INPUT;
    }

    if (*argv[1] == '-')
    {
        return INVALID_INPUT;
    }

    return OK;
}

void a(char* c_eps, char* c_x, double* result){
    double eps = atof(c_eps);
    double x = atof(c_x);
    *result = 0.0;
    double tmp = 1.0;
    int n = 1;

    while (fabs(tmp) > eps) 
    {
        *result += tmp;
        tmp *= x / n;
        n++;
    }
}
void b(char* c_eps, char* c_x, double* result){
    double eps = atof(c_eps);
    double x = atof(c_x);
    *result = 0.0;
    double tmp = 1.0;
    int n = 1;
    while (fabs(tmp) > eps)
    {
        *result += tmp;
        tmp *= -1. * x * x / (2 * n * (2 * n - 1.));
        n++;
    }
}
void c(char* c_eps, char* c_x, double* result){
    double eps = atof(c_eps);
    double x = atof(c_x);
    *result = 0.0;
    double tmp = 1.0;   
    int n = 1;
    while(fabs(tmp) > eps)
    {
        *result += tmp;
        tmp *= (9.0 * n * n * x * x) / (9.0 * n * n - 9.0 * n + 2.0);
        n++;
    }
}
void d(char* c_eps, char* c_x, double* result){
    double eps = atof(c_eps);
    double x = atof(c_x);
    *result = 0.0;
    double tmp = -1.0 * x * x / 2.0;;   
    int n = 1;
    while(fabs(tmp) > eps)
    {
        *result += tmp;
        tmp *= (-1.0 * x * x * (2.0 * n - 1)) / (2.0 * n);
        n++;
    }
}
int main(int argc, char** argv){
    if (validator(argc, argv) == INVALID_INPUT)
    {
        puts("Неверный ввод");
        usage();
        return INVALID_INPUT;
    }
    double result;
    if (atof(argv[1]) == 0.)
    {
        puts("0 - недопустимое значение эпсилона");
        return 1;
    }
    a(argv[1], argv[2], &result);
    printf("%.10f\n", result);
    b(argv[1], argv[2], &result);
    printf("%.10f\n", result);
    if (fabs(atof(argv[2])) < 1)
    {
        c(argv[1], argv[2], &result);
        printf("%.10f\n", result);
        d(argv[1], argv[2], &result);
        printf("%.10f\n", result);
    }
    else
    {
        puts("В Суммах c и d: x должен быть в диапозоне {-1 < x < 1}");
    }
}
