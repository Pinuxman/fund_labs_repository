#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define IS_PRIME 1
#define IS_COMPOSITE 0
#define IS_NOT_COMPOSITE_OR_PRIME 2

int string_to_int_converter(char s[]){
    int num = 0;
    unsigned long long digits = strlen(s);
    for (int i = 0; i < digits; ++i) 
    {
        num = num * 10 + (s[i] - '0');
    }
    return num;
}

void counter(int number, int** result, int* count){
    int j = 0;
    for (int i = 1; i <= 100; i++) {
        if (i % number == 0) 
        {
            (*result)[j] = i;
            j++;
        }
    }
    *count = j;
}

int is_prime(int number){
    int temp = 0;
    if (number == 1)
    {
        temp++;
        return IS_NOT_COMPOSITE_OR_PRIME;
    }
    if (number == 2)
    {
        temp++;
        return IS_PRIME;
    }
    if (number % 2 == 0)
    {
        return IS_COMPOSITE;
    }
    for (int i = 3; i < sqrt((double) number); i += 2) 
    {
        if (number % i == 0) 
        {
            return IS_COMPOSITE;
        }
    }
    if (!temp) 
    {
        return IS_PRIME;
    }
}
void separate_number_digits(char** argv){
    unsigned long long temp = strlen(argv[1]);
    for (int i = 0; i < temp; ++i) 
    {
        printf("%c ", argv[1][i]);
    }
    printf("\n");
}
void pow_table(int number, int table[10][10]) {
    int tmp = 1;
    if (number > 10) 
    {
        printf("Entered number is bigger than 10!\n");
    } else 
    {
        for (int i = 1; i <= 10; i++) 
        {
            for (int j = 1; j <= number; j++) 
            {
                tmp *= i;
                table[i - 1][j - 1] = tmp;
            }
            tmp = 1;
        }
    }
}

void print_pow_table(int number, int table[10][10]){
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= number; j++)
        {
            printf("%d ^ %d = %d", i, j, table[i - 1][j - 1]);
        }
        printf("\n");
    }
}
void sum(int number, unsigned int* s) {
    *s = (1 + number) * (number / 2 );
}

unsigned int factorial(unsigned int number) {
    if (number == 0 || number == 1)
    {
        return 1;
    }
    return factorial(number - 1) * number;
}


int main(int argc, char** argv){
    if (argc != 3 || (argv[2][0] != '-' && argv[2][0] != '/'))
    {
        printf("Неверный ввод аргументов!\nВведите: число -флаг\n");
        return 1;
    } 
    if (argv[2][2])
    {
        puts("Неверный ввод флага!");
        return 1;
    }
    int num = string_to_int_converter(argv[1]);
    switch(argv[2][1])
    {
        case 'h':
        {
            if (num > 100)
            {
                puts("Числа не должны не превышать 100");
            }
            else if (num == 0)
            {
                puts("Число не может быть нулем");
                break;
            }
            else 
            {
                int* result = (int*)malloc(100 * sizeof(int));
                if (result == NULL)
                {
                    puts("Маллок упал");
                    return 1;
                }
                int count;
                counter(num, &result, &count);
                for (int i = 0; i < count; i++)
                {
                    printf("%d ", result[i]);
                }
                printf("\n");
                free(result);
                break;
            }
        }
        case 'p':
        {
            if (is_prime(num) == IS_PRIME)
            {
                puts("Число простое");
            }
            else if (is_prime(num) == IS_COMPOSITE)
            {
                puts("Число составное");
            }
            else if (is_prime(num) == IS_NOT_COMPOSITE_OR_PRIME)
            {
                puts("Число не является простым или составным");
            }
            break;
        }
        case 's':
        {
            separate_number_digits(argv);
            break;
        }
        case 'e':
        {
            int table[10][10];
            pow_table(num, table);
            print_pow_table(num, table);
            break;
        }
        case 'a':
        {
            unsigned int s;
            sum(num, &s);
            printf("Сумма %d членов равна: %d\n", num, s);
            break;
        }
        case 'f':
        {
            if (num > 20)
            {
                puts("Значение не может превышать 20");
                break;
            }
            printf("Факториал равен: %u\n", factorial(num));
            break;
        }
    }
    return 0;
}