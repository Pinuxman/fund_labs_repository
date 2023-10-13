#include <stdio.h>

typedef enum{
    OK,
    FILE_ERROR,
    FLAG_ERROR
}status_code;

FILE* in;

status_code validator(int argc, char** argv){
    if (argc != 2)
    {
        puts("Неверное колличество флагов");
        return FLAG_ERROR;
    }
    return OK;
}
status_code create_file(const char* filename){
    in = fopen(filename, "wb");
    if (in == NULL)
    {
        return FILE_ERROR;
    }
    char bytes[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    fwrite(bytes, sizeof(char), sizeof(bytes), in);
    fclose(in);
    return OK;
}

status_code read_file(const char* filename){
    in = fopen(filename, "rb");
    if (in == NULL)
    {
        return FILE_ERROR;
    }
    char bytes[11];
    fread(bytes, sizeof(char), sizeof(bytes), in);
    fseek(in, 0, SEEK_SET);
    char byte;
    while((byte = fgetc(in)) != EOF)
    {
        printf("%d\n", byte);
        printf("_p = %p\n_r = %d\n_w = %d\n_flags = %d\n_file = %d\n_blksize = %d\n_offset = %lld\n", in->_p, in->_r, in->_w, in->_flags, in->_file, in->_blksize, in->_offset);
    }
    fclose(in);
    return OK;
}

status_code fseek_offset(const char* filename){
    in = fopen(filename, "rb");
    if (in == NULL)
    {
        return FILE_ERROR;
    }
    fseek(in, 3, SEEK_SET);
    char bytes[4];
    fread(bytes, sizeof(char), sizeof(bytes), in);
    for (int i = 0; i < 4; i++)
    {
        printf("%d\n", bytes[i]);   
    }
    fclose(in);
    for (int i = 0; i < 4; i++)
    {
        printf("%d\n", bytes[i]);   
    }
    return OK;
}

int main(int argc, char** argv){
    if (validator(argc, argv) == FLAG_ERROR)
    {
        return 1;
    }
    create_file(argv[1]);
    read_file(argv[1]);
    fseek_offset(argv[1]);
}