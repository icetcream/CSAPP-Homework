#include <stdio.h>
int fit_bits(int x, int n){
    //取出x在n位前的位
    //在通过!来判断是否可以表示
    unsigned int a = ~((1<<n) - 1);
    printf("%x\n",a);
    return !(x&a);
}
int main(){
    int a = fit_bits(128,8);
    printf("%d",a);
    return 0;
}