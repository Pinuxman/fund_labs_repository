#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#define ALOC_SIZ 128
#define MAX(a,b) ((a) > (b) ? (a) : (b))

typedef enum{
    BASE_ERROR,
    BAD_ALOC,
    OK
}status_code;

char* string_ascii_to_num_rep(char* str){
    int i = 0;
    while(str[i] != '\0')
    {
        str[i] = (str[i] <= '9') ? (str[i] - '0') : (str[i] - 'A' + 10);
        i++;
    }
    return str;
}

char* string_num_to_ascii_rep(char* str){
    int i = 0;
    while(str[i] != 0)
    {
       str[i] = (str[i] > 9) ? (str[i] + 'A' - 10) : (str[i] + '0');
    }
    return str;
}

char* sum(char* a, char* b, unsigned int base){
    int carry = 0;
    int i = 0;
    while(i < MAX(strlen(a), strlen(b)) || carry)
    {
        if (i == strlen(a))
        {
            a[i] = 0;
        }
        if (i < strlen(b))
        {
            a[i] += carry + b[i];
        }
        else 
        {
            a += carry;
        }
        carry = (a[i] >= base);
        if (carry)
        {
            a[i] -= base;
        }
        i++;
    }
    return a;
}

char* base_sum(unsigned int base, int cnt, ...){
    va_list args;
    char *num, *a, *b;
    num = (char*)malloc(ALOC_SIZ * sizeof(char));
    a = (char*)malloc(ALOC_SIZ * sizeof(char));
    b = (char*)malloc(ALOC_SIZ * sizeof(char));
    va_start(args, cnt);
    while(cnt--)
    {
        strcpy(num, va_arg(args, char*));
        strcpy(a, num);
        cnt--;
        strcpy(num, va_arg(args, char*));
        strcpy(b, num);
        strcpy(a, string_num_to_ascii_rep(sum(string_ascii_to_num_rep(a), string_ascii_to_num_rep(b), base)));
    }
    va_end(args);
    return a;
}

status_code print_err(status_code code){
    if (code == BASE_ERROR)
    {
        printf("base = [2; 36]\n");
        return code;
    }
    if (code == BAD_ALOC)
    {
        printf("aloc err\n");
        return code;
    }
    return OK;
}

int main(){
    char* a = (char*)malloc(ALOC_SIZ * sizeof(char));
    char* b = (char*)malloc(ALOC_SIZ * sizeof(char));
    char* c = (char*)malloc(ALOC_SIZ * sizeof(char));
    strcpy(a, "1");
    strcpy(b, "1");
    strcpy(c, "1");
    char* res = base_sum(16, 3, a, b, c);
    // if (print_err(st) != OK)
    // {
    //     return -1;
    // }
    printf("%s\n", res);
    free(a);
    free(b);
    free(c);
}