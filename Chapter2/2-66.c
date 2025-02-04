#include <stdio.h>
int leftmost_one(unsigned x){
    //转化为0...111...1的形式
    x |= x>>1;
    x |= x>>2;
    x |= x>>4;
    x |= x>>8;
    x |= x>>16;
    return (x+1)>>1;
}
int main()
{
    unsigned a = 0xFF00;
    unsigned b = 0x6600;
    unsigned c = 0;

    printf("%x\n",leftmost_one(a));
    printf("%x\n",leftmost_one(b));
    printf("%x\n",leftmost_one(c));
    return 0;
}