#include <stdio.h>
unsigned rotate_left(unsigned x, int n){
    //先计算左移后的左边和右边
    //再去除为0时候的特殊情况
    int w = sizeof(unsigned)<<3;
    int left = x<<n;
    int right = ((~(1<<(w-n) - 1))&x)>>(w-n);
    int sign = !!n;
    return ((-sign)&(left+right))|((sign-1)&x);
}
int main(){
    unsigned x = 0x12345678;
    printf("%x\n",rotate_left(x,4));
    printf("%x\n",rotate_left(x,20));
    printf("%x",rotate_left(x,0));
    return 0;
}