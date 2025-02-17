## Phase1

读入字符串的地址，和0x402400处的字符串比较是否相等

通过 x/s 0x402400 可得
Border relations with Canada have never been better.

## Phase2
读入六个数
第一次对于第一个数判断是否为1
之后每次乘以2
最后一次判断和第六个数是否相等

## Phase3
Switch语句
读入两个整数
第一个整数要小于等于7
0 0xcf 207
1 0x137 311
2 0x2c3 707
3 0x100 256
4 0x185 389
5 0xce 206
6 0x2aa 682
7 0x147 327

## Phase4

fun4 
```
%rdi = arg1;
%esi = 0;
%rdx = 14;
%eax = %rdx - %esi;
%ecx = %eax;
%ecx <<= 31;
%ecx /= 2;
%ecx = %eax + %rsi;
if(%ecx > %edi){
    edx = rcx - 1;
}
else if(%ecx < %edi){
    esi = rcx + 1;
}
else {
    %eax = 0
}
```
所以说只要arg1满足上面表达式，arg2为0就可以

## Phase5
0x40245e 处的字符串是flyers

0x4024b0 处的字符串是maduiersnfotvbyl

中间的程序大致是将我们字符串的每一个字符的值取其Ascii码的低4位来选择0x4024b0处的字符串所以我们只需要对应

## Phase6

r13 = rsp
rsi = rsp
<read_six_numbers>
r14 = rsp
r12d = 0

phase_A:
    rbp = r13
    eax = *(r13)
    eax--
    if(eax > 5) explode_bomb
    r12d++
    if(r12d != 6){
    ebx = r12d
phase_B:
    rax = ebx
    eax = *(rsp + 4*rax)
    //rbp和rax分别是前一个数和后面所有数若相等就爆炸
    if(*(rbp+0) == eax) explode_bomb 
    ebx++
    if(ebx > 5){
        r13 += 4
        goto phase_A
    }
    goto phase_B
    }
    //当满足六个数小于等于6，且互不相等进行phase_C
    goto phase_C
phase_C:
    rsi = rsp + 24
    rax = r14
    ecx = 7
    //对每个数做7-num
phase_D:
    edx = ecx
    edx -= *(rax)
    *(rax) = edx
    rax += 4
    if(rax != rsi) goto phase_D

    
中间一段大致是将node按照我们给出的值的顺序在栈上进行排列
比如 1 2 3 4 5 6
那么在栈上从底向上的排列就是 node1 node2 node3 node4 node 5 node 6这样的地址排布
之后是按照我们的排布去修改原来的链表顺序
最后是通过判断是否降序来判断是否爆炸所以我们要通过我们给出的数字来控制节点值降序
这个phase_6想了很久最后还是看了解答，给出解答比较详细的地址
[解答](https://juejin.cn/post/6981396257264648229#heading-6)






