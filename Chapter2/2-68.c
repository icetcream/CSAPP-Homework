#include <stdio.h>

int lower_one_mask(int n){
    int x = 1<<(n-1);
    x = (x<<1) - 1;
    return x;
}
int main(){
    printf("%x",lower_one_mask(32));
    return 0;
}