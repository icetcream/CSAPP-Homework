#include<stdio.h>
int odd_ones(unsigned x){
    int n = (x>>16)^x;
    n = (n>>8)^n;
    n = (n>>4)^n;
    n = (n>>2)^n;
    n = (n>>1)^n;
    return n&0b1;
}

int main(){
    int a = odd_ones(-1);
    printf("%x\n",a);
    int b = odd_ones(0x1);
    printf("%x\n",b);
    return 0;
}