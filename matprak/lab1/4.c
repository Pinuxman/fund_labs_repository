#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum{
    OK,
    FLAG_ERROR,
    FILE_ERROR,
}status_code;

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
        fclose(in);
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
status_code latin_symbols_count(char const* in_filename,char const* out_filename){
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
status_code non_latin_arabic_space(char const* in_filename, char const* out_filename){
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
status_code hex_ascii_non_digit(char const* in_filename, char const* out_filename){
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

status_code validator(int argc, char** argv)
{
    if (argc < 3 || argc > 4)
    {
        return FLAG_ERROR;
    }

    if(argv[1][0] != '-' && argv[1][0] != '/')
    {
        return FLAG_ERROR;
    }

    if (argv[1][1] == 'n' && argc != 4 && strlen(argv[1]) != 3)
    {
        return FLAG_ERROR;
    }

    if (argv[1][1] == 'n')
    {
        if(strcmp(argv[2], argv[3]) == 0)
        {
            return FLAG_ERROR;
        }
    }

    return OK;
}

int main(int argc, char** argv)
{
    if (validator(argc, argv) == FLAG_ERROR)
    {
        printf("invalid input\n");
        return FLAG_ERROR;
    }

    char flag;
    char* input_file = argv[2];
    char* output_file = NULL;

    if (argv[1][1] == 'n')
    {
        flag = argv[1][2];
        output_file = argv[3];
    }
    else
    {
        flag = argv[1][1];
        output_file = (char*)malloc(strlen(argv[2]) + 5);
        if (!output_file)
        {
            printf("failed to allocate memory");
            return FLAG_ERROR;
        }

        strcpy(output_file, "out_");
        strcat(output_file, argv[2]);

    }
    switch (flag)
    {
        case 'd':
            if((remove_arabic_nums(input_file, output_file)) == FILE_ERROR)
            {
                printf("error with opening files");
                return FILE_ERROR;
            }
            break;

        case 'i':

            if (latin_symbols_count(input_file, output_file) == FILE_ERROR)
            {
                printf("error with opening files");
                return FILE_ERROR;
            }
            break;

        case 's':
            if(non_latin_arabic_space(input_file, output_file) == FILE_ERROR)
            {
                printf("error with opening files");
                return FILE_ERROR;
            }
            break;

        case 'a':
            if(hex_ascii_non_digit(input_file, output_file) == FILE_ERROR)
            {
                printf("error with opening files");
                return FILE_ERROR;
            }
            break;

        default:
            printf("invalid flag\n");
            break;
    }
    free(output_file);
    return 0;
}