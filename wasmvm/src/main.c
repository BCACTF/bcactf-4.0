#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "vm/stack.h"
#include "vm/value.h"

typedef void* (OPERATION)(int num, ...);

void* c(int num, ...) {
    int b = 0;
   va_list valist;
   va_start(valist, num);
   for (int i = 0; i < num; ++i) b += va_arg(valist, int);

   va_end(valist);
    return (void*) b;
}

void* d(int num, int f) {

    return &c;
}

int main() {
    OPERATION* k = c;
    OPERATION* b = d;

    printf("%p %p\n", k(5, 3, 2, "abc"), b(4));
}