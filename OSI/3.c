#include <stdio.h>

typedef enum{
    OK,
    FILE_ERROR,
    FLAG_ERROR
}status_code;

FILE* src;
FILE* dst;

status_code validator(int argc, char** argv){
    if (argc != 3)
    {
        puts("Неверное колличество флагов");
        return FLAG_ERROR;
    }
    return OK;
}
status_code copy(const char* src_filename, const char* dst_filename){
    src = fopen(src_filename, "rb");
    if (src == NULL)
    {
        return FILE_ERROR;
    }
    dst = fopen(dst_filename, "wb");
    if (dst == NULL)
    {
        return FILE_ERROR;
    }
    char cpy;
    while ((cpy = fgetc(src)) != EOF)
    {
        fputc(cpy, dst);
    }
    fclose(src);
    fclose(dst);
    return OK;
}
int main(int argc, char** argv){
    if (validator(argc, argv) == FLAG_ERROR)
    {
        return 1;
    }
    copy(argv[1], argv[2]);
}