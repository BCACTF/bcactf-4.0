#pragma once

#include "vm/value.h"
#include <stddef.h>

struct vm_stack;
struct vm_stack {
    struct vm_stack* nex;
    struct vm_value val;
};

typedef struct vm_stack vm_stack_t;

/* Returns top of the stack */
/* [i32, f32, i64] -> ({i32} -> {f32} -> {i64}) where i32 is the top */
vm_stack_t* vm_stack_new(vm_value_t* values, size_t value_cnt);

/* Copies top stack value over, returns new top of stack */
vm_stack_t* vm_stack_pop(vm_stack_t* stack, vm_value_t* out);

/* Copies over the value, returns new top of stack */
vm_stack_t* vm_stack_push(vm_stack_t* stack, vm_value_t* value);