# Chapter3

## 3.58

```c
long decode2(long x, long y, long z){
    y = y - z;
    x = x * y;
    return (y<<63>>63)^x;
}
```

## 3.59

```c
/*
x*y = (xh^64 + xl)(yh^64 + yl)
    = 2^128*xh*yh + 2^64*xh*yl + 2^64*yh*xl + xl* yl
    = 2^64*xh*yl + 2^64*yh*xl + xl* yl
    开始的时候先使用符号扩展将原来的的有符号数x和y扩展到128位相当于，获得高位的2^64
    之后计算2^64*xh*yl + 2^64*yh*xl
    xl和yl使用无符号乘法(补码除去符号位置，其他位的含义和原码相同)
    所以使用无符号乘法也可以计算进位
    之后进位和之前计算的高位相加放在%rdx，
    低位相乘算出的结构截断后放在%rax
*/
```
## 3.60

```c
/*
A x %rdi, n %rsi, result %rax, mask %rdx
B mask !=0
C mask << (n%64)
D result |= x&mask
*/
long loop(long x, int n){
    long result = 0;
    long mask =;
    for(mask = 1; mask !=0; mask = mask << (n%64)){
        result |= x&mask;
    }
}
```

## 3.61

```c
/*
条件传送会分别计算两个分支内的值，但是*xp不能取null指针中的值
所以条件传送中不直接取值，先计算地址
*/
long cread_alt(long* xp){
    int t = 0;
    long* p = xp?xp:&t;
    return *p;
}
```

## 3.62

```c
typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t

long switch3(long* p1, long* p2, mode_t action){
    long result = 0;
    switch(action){
        case MODE_A:
            result  = *p2;
            *p2 = *p1;
            break;
        case MODE_B:
            result = *p1;
            result += *p2;
            *p1 = result;
            break;
        case MODE_C:
            *p1 = 59;
            result = *p2;
            break;
        case MODE_D:
            result = *p2;
            *p1 = result;
        case MODE_E:
            result = 27;
            break;
        case default:
            result = 12;
    }
    return result;
}
```

## 3.63

```c
long switch_prob(long x, long n){
    long result = x;
    switch(n){
        case 0:
        case 2:
            result = 8*x;
            break;
        case 3:
            result = x>>3;
            break;
        case 4:
            result = 15*x;
            x = result;
        case 5:
            x = x*x;
        default:
            result = x + 75;
    }
    return result;
}
```

## 3.64

```c
/*
A:
    A[i] = *(A+i);
    A[i][j] = *(A+i*T+j);
    A[i][j][k] = *(A+i*S*T+j*T+k);
B:
    通过汇编可以得到
    dest = A + 65*i + 13*j + K;
    R*S*T = 3640/8
    R = 7, T = 13, S = 5;
*/
```

## 3.65

```c
/* 
A:%rdx
B:%rax
C:M = 120/8 = 15 
*/
```

## 3.66

```c
/*
NR: #define NR(n) (3 * (n))
NC: #define NC(n) (4 * (n) + 1)
*/
long sum_col(long n, long A[NR(n)][NC(n)], long j) {
	long i;
	long result = 0;
	for (i = 0; i < NR(n); i++)
		result += A[i][j];
	return result;
}
```

## 3.67

```c
/*
A:
    x (%rsp)
    y 8(%rsp)
    &z 16(%rsp)
    z 24(%rsp)
B:
    原rsp+64,x,y,&z
C:
    通过原先存储在栈中的值和%rsp
D:
    通过原先设置的%rip的值
E:
    r.u[0] 64(%rsp)
    r.u[1] 72(%rsp)
    r.q 80(%rsp)
F:
    通过通用的栈和寄存器来传递
*/
```

## 3.68

```c
/*
考虑数据对齐
setVal:
    movslq 8(%rsi), %rax B [5,8] 
    addq 32(%rsi), %rax A [6,10]
    movq %rax, 184(%rdi) A*B [180,184]
    ret
    解得 A = 9 B = 5
*/
```

## 3.69

```c
/*
A: CNT = 7;
B: 
    struct{
        long idx;
        long x[4];
    }a_struct
*/
```

## 3.70

```c
/*
A: 
    e1.p 0
    e1.y 8
    e2.x 0
    e2.next 8
B: 16
*/
void proc(union ele *up){
    up->x = *((e2->next)->p)-(e->next)->y;
}
```

## 3.71
```c
#include <stdio.h>

int main() {
    char buffer[100]; 

    printf("请输入一行文本：\n");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("您输入的文本是：%s", buffer);
    } else {
        printf("读取失败！\n");
    }

    return 0;
}
```

## 3.72

```c
/*
A:
  n为奇数的时候 (8*n+30)&0xFFFFFFF0 为8*n+24
  n为偶数的时候 (8*n+30)&0xFFFFFFF0 为8*n+16
  s2 = s1 - (8*n+30)&0xFFFFFFF0
B:
  p = (rsp+15)&0xFFFFFFF0 取最近的满足16除的地址
C:
  最大:n为奇数 s2地址为16可除
  最小:n为偶数 s2地址为16k-15格式
D:
  s2满足保持偏移量的最接近16的数
  p满足对于16对齐
*/
```
## 3.73

```
find_range:
    mov 0x0, %eax
    vxorps %xmm1,%xmm1,%xmm1
    vucomiss %xmm0,%xmm1
    jp  .L5
    jc  .L6
    je  .L7
    ret
L5:
    mov 0x3, %eax
    ret
L6:
    mov 0x2, %eax
    ret
L7:
    mov 0x1, %eax
    ret
```

## 3.74

```
find_range:
    mov 0x0, %eax
    mov 0x1, %edi
    mov 0x2, %esi
    mov 0x3, %edx
    vxorps %xmm1,%xmm1,%xmm1
    vucomiss %xmm0,%xmm1
    cmove %edi, %eax
    cmovs %esi, %eax
    cmovp %edx, %eax
```

## 3.75

```c
/*
A:
    从减法的函数中可以得到，使用了两个xmm寄存器来分别存储
    实部和虚部，计算的时候分别计算
B:
    实数存在低位的那个xmm寄存器，虚部存在高位的那个xmm寄存器
*/

