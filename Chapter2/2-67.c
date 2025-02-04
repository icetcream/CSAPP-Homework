/*  
    A:左移数大于了int的机器位数
*/
#include <stdio.h>
int int_size_is_32_B(){
    int a = 1<<31;
    return !(a<<1);
}

int int_size_is_32_C(){
    int a = 1<<15;
    int b = a<<15;
    return !(b<<2)&&(a<<1);
}

int main(){
    int a = int_size_is_32_B();
    int b = int_size_is_32_C();
    printf("%d  \n%d",a,b);
    return 0;
}