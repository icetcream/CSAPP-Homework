#include <stdio.h>
int int_shifts_are_arithmetic(){
    int a = -1;
    int b = a>>1;
    return a==b;
}
int main(){
    printf("%d",int_shifts_are_arithmetic());
    return 1;
}