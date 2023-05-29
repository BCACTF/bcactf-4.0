#pragma once

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

typedef int32_t i32_t;
typedef uint32_t u32_t;
typedef float f32_t;
typedef int64_t i64_t;
typedef uint64_t u64_t;
typedef double f64_t;

enum vm_valuetype {
    vm_kI32,
    vm_kF32,
    vm_kI64,
    vm_kF64
};

struct vm_value {
    // enum vm_valuetype type;
    union {
        i32_t i32_val;
        f32_t f32_val;
        i64_t i64_val;
        f64_t f64_val;

        i64_t raw_val;
    };
};

typedef struct vm_value vm_value_t;

void vm_value_i32_init(vm_value_t* out, i32_t value);
void vm_value_f32_init(vm_value_t* out, f32_t value);
void vm_value_i64_init(vm_value_t* out, i64_t value);
void vm_value_f64_init(vm_value_t* out, f64_t value);