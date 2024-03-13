#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum status_code
{
    SUCCESS,
    INVALID_INPUT,
    FILE_ERROR
}status_code;

int is_separator(char c)
{
    if(c == ' ' || c == '\n' || c == '\t'){return 1;}
    return 0;
}

int decimal_to_base(int number, int base)
{
    int res = 0;
    int n = 1;
    while(number > 0)
    {
        int reminder = number % base;
        res += reminder * n;
        number /= base;
        n*= 10;
    }
    return res;
}

status_code flag_r(char* file_1, char* file_2, char* file_3)
{
    FILE* file_in_1 = fopen(file_1, "r");

    if(file_in_1 == NULL)
    {
        return FILE_ERROR;
    }

    FILE* file_in_2 = fopen(file_2,"r");

    if(file_in_2 == NULL)
    {
        fclose(file_in_1);
        return FILE_ERROR;
    }

    FILE* file_out = fopen(file_3, "w");

    if(!file_out)
    {
        fclose(file_in_1);
        fclose(file_in_2);
        return FILE_ERROR;
    }

    char buffer[128];
    bool flag_1, flag_2;

    while(true)
    {
        flag_1 = false;
        flag_2 = false;

        if(fscanf(file_in_1, "%s", buffer) != EOF) 
        {
            flag_1 = true;
            fprintf(file_out, "%s ", buffer);
        }

        if(fscanf(file_in_2, "%s", buffer) != EOF)
        {
            flag_2 = true;
            fprintf(file_out, "%s ", buffer);
        }

        if(!(flag_1 & flag_2))
        {
            break;
        }
    }
    fclose(file_in_1);
    fclose(file_in_2);
    fclose(file_out);
    return SUCCESS;
}

status_code flag_a(char const * file_in, char const* file_out)
{
    FILE* file_input = fopen(file_in, "r");

    if(file_input == NULL)
    {
        return FILE_ERROR;
    }

    FILE* file_output = fopen(file_out, "w");

    if(file_output == NULL)
    {
        fclose(file_input);
        return FILE_ERROR;
    }

    int position = 0;
    char s = fgetc(file_input);
    while(s != EOF)
    {
       while(is_separator(s))
       {
            s = fgetc(file_input);
       }
       position++;

       if(position % 10 == 0)
       {

        while(!is_separator(s) && s != EOF)
        {
            if (isalpha(s))
            {
                fprintf(file_output, "%d", decimal_to_base(toascii(tolower(s)), 4));
            }

            else
            {
                fputc(s, file_output);
            }
            s = fgetc(file_input);
        }
       }

       else if (((position & 1) == 0) && (position % 10) != 0)
       {
            while(!is_separator(s) && s != EOF)
            {
                if(isalpha(s))
                {
                    fputc(tolower(s), file_output);
                }
                else
                {
                    fputc(s, file_output);
                }
                s = fgetc(file_input);
            }
       }

       else if((position % 10) == 5)
       {
            while(!is_separator(s)  && s != EOF)
            {
                fprintf(file_output, "%d", decimal_to_base(toascii(s), 8));
                s = fgetc(file_input);
            }
       }

       else
       {
            while(!is_separator(s) && s != EOF)
            {
                fputc(s, file_output);
                s = fgetc(file_input);
            }
       }
       fputc(' ', file_output);
    }
    fclose(file_input);
    fclose(file_output);
    return SUCCESS;
}

status_code check_input(int argc, char* argv[])
{
    if(argv[1][0] != '-' && argv[1][0] != '/')
    {
        return INVALID_INPUT;
    }

    if ((argv[1][1] == 'r') && argc != 5)
    {
        return INVALID_INPUT;
    }

    if((argv[1][1] == 'a') && argc != 4) 
    {
        return INVALID_INPUT;
    }

    return SUCCESS;
}

int main(int argc, char* argv[])
{

    if (check_input(argc, argv) == INVALID_INPUT)
    {
        printf("invalid input\n");
        return INVALID_INPUT;
    }
    char flag = argv[1][1];

    switch(flag)
    {
        case 'r':

            if(flag_r(argv[2], argv[3], argv[4]) == FILE_ERROR)
            {
                printf("error with opening file\n");
                return FILE_ERROR;
            }
            else
            {
                printf("flag r complete!\n");
            }
            break;

        default:
            printf("invalid flag\n");
            return INVALID_INPUT;

        case 'a':
            if(flag_a(argv[2], argv[3]) == FILE_ERROR)
            {
                printf("error with opening file\n");
                return FILE_ERROR;
            }
            else
            {
                printf("flag a complete\n");
            }
    }
    return 0;
}
