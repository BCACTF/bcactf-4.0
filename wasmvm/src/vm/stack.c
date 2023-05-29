#include "vm/stack.h"

#include <stdlib.h>

vm_stack_t* vm_stack_new(vm_value_t* values, size_t value_cnt) {
    if (value_cnt == 0) return NULL;
#ifdef DEBUG
    assert(values != NULL);
#endif

    if (values == NULL) return NULL;

    vm_stack_t* stack = NULL;

    // push it backwards - using our trusty `-->` operator
    while (value_cnt --> 0) {
        stack = vm_stack_push(stack, &values[value_cnt]);
    }

    return stack;
}


/* Copies top stack value over, returns new top of stack */
vm_stack_t* vm_stack_pop(vm_stack_t* stack, vm_value_t* out) {
#ifdef DEBUG
    assert(stack != NULL);
#endif

    if (stack == NULL) return NULL;

    // out->type = stack->val.type;
    out->raw_val = stack->val.raw_val;

    vm_stack_t* top = stack->nex;
    free(stack);

    return top;
}

/* Copies over the value, returns new top of stack */
vm_stack_t* vm_stack_push(vm_stack_t* stack, vm_value_t* value) {
#ifdef DEBUG
    assert(value != NULL);
#endif

    if (value == NULL) return NULL;

    vm_stack_t* top = malloc(sizeof(vm_stack_t));

    // top->val.type = value->type;
    top->val.raw_val = value->raw_val;
    top->nex =  stack;

    return top;
}