#include<stdio.h>
unsigned srl(unsigned x, int k){
    unsigned xsra = (int)x >>k;
    //使用左移得到前面为一后面为0的二进制数
    //位反转后用或操作来实现用算数右移逻辑右移
    int a = ~0x0;
    int lenInt = 8*sizeof(int);
    int b = a<<(lenInt-k);
    return xsra&(~b);
}
unsigned sra(unsigned x, int k){
    int xsrl = (unsigned)x >>k;
    int a = ~0x0;
    int lenInt = 8*sizeof(int);
    int b = a<<(lenInt-k);
    //得到符号位
    int signB = (0b1<<(lenInt-1))&x;
    //将1转成-1实现对于操作数的条件判断
    return xsrl|(-!!signB&b);
}
int main(){
    unsigned FirstTest = srl(0xF2345678,8);
    printf("First Test %x\n",FirstTest);
    unsigned SecondTest = sra(0xF2345678,8);
    printf("Second Test %x\n",SecondTest); 
    return 0;
}