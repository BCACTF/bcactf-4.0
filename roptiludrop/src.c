#include <stdio.h>
#include <stdlib.h>

void DANCE() {
    __asm("push %rax");
    __asm("pop %rax");
}

void DAOCE() {
    __asm("push %rbx");
    __asm("pop %rbx");
}

void DROCE() {
    __asm("push %rcx");
    __asm("pop %rcx");
}

void ROCE() {
    __asm("push %rdx");
    __asm("pop %rdx");
}

void ROPE() {
    __asm("push %rsi");
    __asm("pop %rsi");
} 

void ROP() {
    __asm("push %rdi");
    __asm("pop %rdi");
} 

void life() {
    char future[16];

    printf("DO NOT STOP ROPPING\n> ");
    gets(future);
    printf(future);

    printf("What is this? %p\n", (void*)printf);

    printf("\nDO NOT STOP ROPPING\n> ");
    fread(future, 1, 80, stdin);
    puts(future);
}

int main() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    setbuf(stderr, NULL);

    life();

    puts("Party!");
    return 0;
}