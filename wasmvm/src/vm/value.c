#include "vm/value.h"

#include "vm/stack.h"

void vm_value_i32_init(vm_value_t* out, i32_t value) {
    // out->type = vm_kI32;
    out->i32_val = value;
}

void vm_value_f32_init(vm_value_t* out, f32_t value) {
    // out->type = vm_kF32;
    out->f32_val = value;
}

void vm_value_i64_init(vm_value_t* out, i64_t value) {
    // out->type = vm_kI64;
    out->i64_val = value;
}

void vm_value_f64_init(vm_value_t* out, f64_t value) {
    // out->type = vm_kF64;
    out->f64_val = value;
}