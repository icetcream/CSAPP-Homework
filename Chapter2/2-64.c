#include <stdio.h>
int any_odd_one(unsigned x){
    x = (x>>16)|x;
    x = (x>>8)|x;
    x = (x>>4)|x;
    x = (x>>2)|x;
    return !!(x&0b10);
}

int main(){
    printf("%x\n",any_odd_one(0x0020));
    printf("%x\n",any_odd_one(0x0010));
    return 0;
}