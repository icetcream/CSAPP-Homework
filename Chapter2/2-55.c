#include <stdio.h>
#include <stddef.h>  // 添加这一行以包含 size_t 的定义

typedef unsigned char *pointer;

void show_bytes(pointer start, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%p: %02x\n", start + i, *(start + i));
    }
}

int main() {
    int a = 0x1234578;
    show_bytes((pointer) &a, sizeof(int));
    return 0;
}