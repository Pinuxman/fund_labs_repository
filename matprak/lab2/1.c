#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
typedef enum{
    FLAG_ERROR,
    ARGS_ERROR,
    OK
}status_code;

status_code param_validator (int argc, char** argv) {
    if (argc < 3) 
    {
        return ARGS_ERROR;
    }
    if (argv[1][0] != '-' || argv[1][2] != '\0') 
    {
        return FLAG_ERROR;
    }

    if (argv[1][1] == 'c' && argc < 4) 
    {
        return ARGS_ERROR;
    } 
    else if (argv[1][1] != 'c' && argc != 3) 
    {
        return ARGS_ERROR;
    }
}

size_t str_len(char* string){
    size_t size = 0;
    while (*string++ != '\0')
    {
        size++;
    }
    return size;
}

char* reverse(const char* string){
    int size = str_len(string);
    char* new = (char*)malloc(sizeof(string) + 1);
    for (int i = 0; i < size; i++)
    {
        new[i] = string[size - i - 1];
    }
    new[size + 1] = '\0';
    return new;
}

char* h_register(const char* string){
    char* new = (char*)malloc(sizeof(string) + 1);
    int i = 0;
    for (; i <= str_len(string); i++)
    {
        if(i % 2 == 0)
        {
            new[i] = toupper(string[i]);
        }
        else
        {
            new[i] = string[i];
        }
    }
    new[i + 1] = '\0';
    return new;
}

char* str_sort(const char* string){
    char* new = (char*)malloc(sizeof(string) + 1);
    int j = 0;
    for (int i = 0; i < str_len(string); i++)
    {
        if(isdigit(string[i]))
        {
            new[j++] = string[i];
        }
    }
    for (int i = 0; i < str_len(string); i++)
    {
        if (isalpha(string[i]))
        {
            new[j++] = string[i];
        }
    }
    for (int i = 0; i < str_len(string); i++)
    {
        if (!isalnum(string[i]))
        {
            new[j++] = string[i];
        }
    }
    return new;
}

char* str_cat(int argc, char** argv){
    int seed = atoi(argv[3]);
    srand(seed);
    int res_length = str_len(argv[2]) + 1;
    char* new_str = (char*) calloc(res_length + 1, sizeof(char));
    for (int i = 0; i < res_length; ++i) {

        new_str[i] = argv[2][i];
    }
    int range = argc - 4;
    for (int i = 0; i < range; i++) {
        int ind1 = rand() % range + 4;
        int ind2 = rand() % range + 4;
        char* temp = argv[ind1];
        argv[ind1] = argv[ind2];
        argv[ind2] = temp;
    }
    for (int i = 4; i < argc; ++i) {
        int temp_length = str_len(argv[i]);
        int n = res_length - 1;
        res_length += temp_length;
        realloc(new_str, res_length + 1);
        for (int j = 0; j < temp_length; ++j) {
            new_str[n + j] = argv[i][j];
        }
    }
    new_str[res_length - 1] = '\0';
    return new_str;
}

int status(int argc, char** argv){
    if (param_validator(argc, argv) == ARGS_ERROR)
    {
        puts("Неверное число флагов");
        return 1;
    }
    if (param_validator(argc, argv) == FLAG_ERROR)
    {
        puts("Флаги введены неверно");
        return 1;
    }
}


status_code flag_caller(int argc, char** argv){
    char flag = argv[1][1];
    switch (flag) {
        case 'l':
            printf("%zu\n", str_len(argv[2])); break;
        case 'r':
            char* tmp = reverse(argv[2]);
            if (tmp == NULL)
            {
                puts("mem non alocated");
                break;
            }
            printf("%s\n", tmp); 
            free(tmp);
            break;
            
        case 'u':
            char* tmp = h_register(argv[2]);
            if (tmp == NULL)
            {
                puts("mem non alocated");
                break;
            }
            printf("%s\n", tmp); 
            free(tmp);
            break;
        case 'n':
            char* tmp = str_sort(argv[2]);
            if (tmp == NULL)
            {
                puts("mem non alocated");
                break;
            }
            printf("%s\n", tmp); 
            free(tmp);
            break;
        case 'c':
            char* tmp = str_cat(argc, argv);
            if (tmp == NULL)
            {
                puts("mem non alocated");
                break;
            }
            printf("%s\n", tmp); 
            free(tmp);
            break;
        default:
            return FLAG_ERROR;
    }
    return OK;
}

int main(int argc, char** argv){

    status(argc, argv);
    if (flag_caller(argc, argv) == FLAG_ERROR)
    {
        puts("Флаги введены неверно");
        return 1;
    } 


    return 0;
}
