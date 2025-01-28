#include <stdio.h>
#include <stddef.h>  // 添加这一行以包含 size_t 的定义

typedef unsigned char *pointer;

void show_bytes(pointer start, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%p: %02x\n", start + i, *(start + i));
    }
}

int main() {
    short a = 0x1234;
    show_bytes((pointer) &a, sizeof(short));
    printf("\n");

    long b = 0x1234567890123456;
    show_bytes((pointer) &b, sizeof(long));
    printf("\n");

    double c = 1024.0;
    show_bytes((pointer) &c, sizeof(double));
    printf("\n");
    return 0;
}