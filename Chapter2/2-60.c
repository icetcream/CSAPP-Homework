#include <stdio.h>
unsigned replace_byte(unsigned x, int i, unsigned char b){
    unsigned replace_location = 0xFF<<(i*8);
    printf("%x %x\n",~replace_location,replace_location);
    return (x&(~replace_location))+(b<<(i*8));
}
int main(){
    unsigned int a = replace_byte(0x12345678,2,0xAB);
    printf("%x \n",a);
    unsigned int b = replace_byte(0x12345678,0,0xAB);
    printf("%x \n",b);
    return 1;
}