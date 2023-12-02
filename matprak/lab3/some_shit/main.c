#include <stdio.h>
#include <stdlib.h>

int sub(int minuend, int subtrahend){
    int borrow = 0;
    while(subtrahend)
    {
        borrow = ((~minuend) & subtrahend);
        minuend = minuend ^ subtrahend;
        subtrahend = (borrow << 1);
    }
    return minuend;
}

char* ret_2_r(int num, unsigned int r){
    int rep[32];
    for (int i = 31; i >= 0; i--)
    {
        rep[i] = num & sub((1 << r), 1);
        num >>= r;
    }
    char* res = (char*)malloc(sizeof(char) * 33);
    for (int i = 0; i < 32; i++)
    {
        res[i] = (rep[i] > 9) ? (rep[i] + 'A' - 10) : (rep[i] + '0');
    }
    res[32] = '\0';
    return res;
}



int main(){
    char* res = ret_2_r(10, 4);
    if (res == NULL)
    {
        printf("mem not allocated\n");
        return 1;
    }
    printf("%s\n", res);
    free(res);
    return 0;
}
