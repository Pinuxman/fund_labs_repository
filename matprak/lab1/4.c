#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum{
    OK,
    FLAG_ERROR,
    FILE_ERROR,
}status_code;

status_code validator(int argc, char** argv){
    if (argc < 3 || argc > 4)
    {
        puts("Параметров должно быть либо 3 либо 4");
        return FLAG_ERROR;
    }
}

char* out_prefix_add(char* in){
    char _out[20] = "out_";
    strcat(_out, in);
    return _out;
}

status_code remove_arabic_nums(const char* in_filename, const char* out_filename){
    char digit;
    FILE* in = fopen(in_filename, "r");
    if (in == NULL)
    {
        return FILE_ERROR;
    }
    FILE* out = fopen(out_filename, "w");
    if (out == NULL)
    {
        return FILE_ERROR;
    }
    while ((digit = fgetc(in)) != EOF)
    {
        if (!isdigit(digit)) 
        {
            fputc(digit, out);
        }
    }
    fclose(in);
    fclose(out);
    return OK;
}
status_code latin_symbols_count(const char* in_filename, const char* out_filename){
    int count = 0;
    FILE* in = fopen(in_filename, "r");
    if (in == NULL)
    {
        return FILE_ERROR;
    }
    FILE* out = fopen(out_filename, "w");
    if (out == NULL)
    {
        fclose(in);
        return FILE_ERROR;
    }
    char latin_symbol;
    while ((latin_symbol = fgetc(in)) != EOF)
    {
        if (isalpha(latin_symbol))
        {
            count++;
        }
        if (latin_symbol == '\n')
        {
            fprintf(out, "%d\n", count);
            count = 0;
        }
    }
    fclose(in);
    fclose(out);
    return OK;
}
status_code non_latin_arabic_space(const char* in_filename, const char* out_filename){
    int count = 0;
    FILE* in = fopen(in_filename, "r");
    if (in == NULL)
    {
        fclose(in);
        return FILE_ERROR;
    }
    FILE* out = fopen(out_filename, "w");
    if (out == NULL)
    {
        fclose(out);
        return FILE_ERROR;
    }
    char non_latin_arabic_space;
    while ((non_latin_arabic_space = fgetc(in)) != EOF)
    {
        if (!(isalnum(non_latin_arabic_space) || non_latin_arabic_space == ' '))
        {
            count++;
        }
        if (non_latin_arabic_space == '\n')
        {
            fprintf(out, "%d\n", count);
            count = 0;
        }
    }
    fclose(in);
    fclose(out);
    return OK;
}
status_code hex_ascii_non_digit(const char* in_filename, const char* out_filename){
    FILE* in = fopen(in_filename, "r");
    if (in == NULL)
    {
        fclose(in);
        return FILE_ERROR;
    }
    FILE* out = fopen(out_filename, "w");
    if (out == NULL)
    {
        fclose(out);
        return FILE_ERROR;
    }
    char hex_ascii_non_digit;
    while ((hex_ascii_non_digit = fgetc(in)) != EOF)
    {
        if (!isdigit(hex_ascii_non_digit))
        {
            fprintf(out, "%X", hex_ascii_non_digit);
        }
        else 
        {
            fputc(hex_ascii_non_digit, out);
        }
    }
    fclose(in);
    fclose(out);
    return OK;
}
int main(int argc, char** argv){
    if (validator(argc, argv) == FLAG_ERROR)
    {
        return 1;
    }
    if (argv[1][1] == 'n')
    {
        switch (argv[1][2])
        {
        case 'd':
        {
            remove_arabic_nums(argv[2], argv[3]);
            break;
        }
        case 'i':
        {
            latin_symbols_count(argv[2], argv[3]);
            break;   
        }
        case 's':
        {
            non_latin_arabic_space(argv[2], argv[3]);
            break;
        }
        case 'a':
        {
            hex_ascii_non_digit(argv[2], argv[3]);
            break;
        }
        default:
            break;
        }
    }
    else if(argc == 3)
    {
        char* out_prefix = (char*)malloc(sizeof(char) * BUFSIZ);
        if (out_prefix == NULL)
        {
            puts("Ошибка памяти");
            return 1;
        }
        strcpy(out_prefix, argv[2]);
        switch (argv[1][1])
        {
        case 'd':
        {
            remove_arabic_nums(argv[2], out_prefix_add(out_prefix));
            break;
        }
        case 'i':
        {
            latin_symbols_count(argv[2], out_prefix_add(out_prefix));
            break;   
        }
        case 's':
        {
            non_latin_arabic_space(argv[2], out_prefix_add(out_prefix));
            break;
        }
        case 'a':
        {
            hex_ascii_non_digit(argv[2], out_prefix_add(out_prefix));
            break;
        }
        default:
            break;
        }
        free(out_prefix);
    }
}