#include <stdio.h>
int is_little_endian(){
    unsigned int a = 0x1;
    char* aLittle = (char*)&a;
    return *aLittle == a;
}
int main(){
    int result = is_little_endian();
    printf("%d",result);
    return 0;
}