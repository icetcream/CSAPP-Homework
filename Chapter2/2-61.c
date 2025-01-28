#include <stdio.h>
int main(){
    int FirstParam = ~0x0;
    printf("first Param %x\n",FirstParam);
    int FirstExpression = !((~0x0)^FirstParam);
    printf("first Expression %x\n",FirstExpression);

    int SecondParam = 0x0;
    printf("second Param %x\n",SecondParam);
    int SecondExpression = !((0x0)^SecondParam);
    printf("second Expression %x\n",SecondExpression);

    int ThirdParam = 0x123456FF;
    printf("third Param %x\n",ThirdParam);
    int ThirdExpression = !((ThirdParam&0xFF)^0xFF);
    printf("third Expression %x\n",ThirdExpression);

    int FourParam = 0x0;
    printf("four Param %x\n",FourParam);
    int FourExpression = !((FourParam>>((sizeof(int)-1)<<3))&0xFF);
    printf("four Expression %x\n",FourExpression);
}