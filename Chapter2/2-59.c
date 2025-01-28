#include <stdio.h>
int main(){
    unsigned int x = 0x89ABCDEF;
    unsigned int y = 0x76543210;
    unsigned int expression = (x&0b11111111) + (y>>8<<8);
    printf("%x",expression);
}