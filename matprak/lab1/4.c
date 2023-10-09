#include <stdio.h>
#include <string.h>
#include <ctype.h>
void remove_arabic_nums(const char* in_filename, const char* out_filename){
    char digit;
    FILE* in = fopen(in_filename, "r");
    if (in == NULL)
    {
        fclose(in);
    }
    FILE* out = fopen(out_filename, "w");
    if (out == NULL)
    {
        fclose(out);
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
}
void latin_symbols_count(const char* in_filename, const char* out_filename){
    int count = 0;
    FILE* in = fopen(in_filename, "r");
    FILE* out = fopen(out_filename, "w");
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
}
void non_latin_arabic_space(const char* in_filename, const char* out_filename){
    int count = 0;
    FILE* in = fopen(in_filename, "r");
    FILE* out = fopen(out_filename, "w");
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
}
void hex_ascii_non_digit(const char* in_filename, const char* out_filename){
    FILE* in = fopen(in_filename, "r");
    FILE* out = fopen(out_filename, "w");
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
}
int main(int argc, char** argv){
    /*if (argc != 3 || argc != 4)
    {
        puts("Invalid number of params...");
    }*/
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
}