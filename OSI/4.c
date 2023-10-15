#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum{
    OK,
    FILE_ERROR,
    FLAG_ERROR
}status_code;

FILE* in;

status_code validator(int argc, char** argv){
    if (argc < 3 || argc > 4)
    {
        puts("Неверное колличество флагов");
        return FLAG_ERROR;
    }
    return OK;
}

void matching (FILE* input, unsigned long int *res, unsigned long int hex)
{
    unsigned long int num = 0;
    fread(&num, sizeof(int), 1, input);
    do 
    {
        if (hex ^ (num == 0))
        {
            (*res)++;
        } 
    } while (fread(&num, sizeof(int), 1, input));
}

int num_check (char* str, unsigned long int *res)
{

    char* end_ptr;

    if ((*res = strtol(str, &end_ptr, 16)) < 0)
    {
        return 1;
    }
    if (end_ptr == str + strlen(str)) {
        return 0;
    
    }else{return 1;}
}

void sum_bytes (FILE* input, unsigned long long int *res)
{
    unsigned char c;
    while (fread(&c, sizeof(char), 1, input))
    {
        *res = (*res ^ c);
    }
}

status_code xor8(const char* filename){
    in = fopen(filename, "rb");
    if (in == NULL)
    {
        return FILE_ERROR;
    }
    char result = 0;
    char byte;
    while ((byte = fgetc(in)) != EOF)
    {
        result ^= byte;
    }
    printf("0x%X\n", result);
    fclose(in);
    return OK;
}

status_code xor32(const char* filename){
    in = fopen(filename, "rb");
    if (in == NULL)
    {
        return FILE_ERROR;
    }
    int result = 0;
    char tmp;
    while(fread(&tmp, sizeof(int), 1, in))
    {
        result ^= tmp;
    }
    tmp = 0;
    char temp1;
    while (fread(&tmp, sizeof(char), 1, in))
    {
        tmp = tmp << 8;
        tmp = tmp | temp1;
    }
    result = result ^ tmp;
    printf("0x%X\n", result);
    fclose(in);
    return OK;
}

status_code mask (char* filename, char* hex)
{
    FILE* in = fopen(filename, "rb");
    if (in == NULL)
    {
        return FILE_ERROR;
    }
    unsigned long int hex_num = 0;
    if (num_check(hex, &hex_num) != 0)
    {
        printf("invalid number\n");
        return 0;
    }
    unsigned long int meeted_amount = 0;
    matching(in, &meeted_amount, hex_num);
    printf("Mask result: %lu\n", meeted_amount);
    fclose(in);
    return OK;
}

int main(int argc, char** argv){
    if (validator(argc, argv) == FLAG_ERROR)
    {
        return 1;
    }
    if (!strcmp(argv[2], "xor8"))
    {
        if(xor8(argv[1]) == FILE_ERROR)
        {
            puts("Файл не открылся");
            return 1;
        }
    }
    else if (!strcmp(argv[2], "xor32"))
    {
        if (xor32(argv[1]) == FILE_ERROR)
        {
            puts("Файл не открылся");
            return 1;
        }
    }
    else if (!strcmp(argv[2], "mask"))
    {
        if (mask(argv[1], argv[3]) == FILE_ERROR)
        {
            puts("Файл не открылся");
            return 1;
        }
    }
}