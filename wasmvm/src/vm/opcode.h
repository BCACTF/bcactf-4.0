#include <stdio.h>

#include "vm/value.h"
#include "vm/stack.h"

enum vm_opcode {
    vm_op_kUnreachable = 0x00,
    vm_op_kNop = 0x01,
    vm_op_kBlock = 0x02,
    vm_op_kLoop = 0x03,
    vm_op_kIf = 0x04,
    vm_op_kElse = 0x05,
    vm_op_kEnd = 0x0B,
    vm_op_kBr = 0x0C,
    vm_op_kBrIf = 0x0D,
    vm_op_kBrTable = 0x0E,
    vm_op_kReturn = 0x0F,
    vm_op_kCall = 0x10,
    vm_op_kCallIndirect = 0x11,
    vm_op_kDrop = 0x1A,
    vm_op_kSelect = 0x1B,
    vm_op_kSelectWithType = 0x1C,
    vm_op_kLocalGet = 0x20,
    vm_op_kLocalSet = 0x21,
    vm_op_kLocalTee = 0x22,
    vm_op_kGlobalGet = 0x23,
    vm_op_kGlobalSet = 0x24,
    vm_op_kTableGet = 0x25,
    vm_op_kTableSet = 0x26,
    vm_op_kI32Load = 0x28,
    vm_op_kI64Load = 0x29,
    vm_op_kF32Load = 0x2A,
    vm_op_kF64Load = 0x2B,
    vm_op_kI32Load8_S = 0x2C,
    vm_op_kI32Load8_U = 0x2D,
    vm_op_kI32Load16_S = 0x2E,
    vm_op_kI32Load16_U = 0x2F,
    vm_op_kI64Load8_S = 0x30,
    vm_op_kI64Load8_U = 0x31,
    vm_op_kI64Load16_S = 0x32,
    vm_op_kI64Load16_U = 0x33,
    vm_op_kI64Load32_S = 0x34,
    vm_op_kI64Load32_U = 0x35,
    vm_op_kI32Store = 0x36,
    vm_op_kI64Store = 0x37,
    vm_op_kF32Store = 0x38,
    vm_op_kF64Store = 0x39,
    vm_op_kI32Store8 = 0x3A,
    vm_op_kI32Store16 = 0x3B,
    vm_op_kI64Store8 = 0x3C,
    vm_op_kI64Store16 = 0x3D,
    vm_op_kI64Store32 = 0x3E,
    vm_op_kMemorySize = 0x3F,
    vm_op_kMemoryGrow = 0x40,
    vm_op_kI32Const = 0x41,
    vm_op_kI64Const = 0x42,
    vm_op_kF32Const = 0x43,
    vm_op_kF64Const = 0x44,
    vm_op_kI32Eqz = 0x45,
    vm_op_kI32Eq = 0x46,
    vm_op_kI32Ne = 0x47,
    vm_op_kI32Lt_S = 0x48,
    vm_op_kI32Lt_U = 0x49,
    vm_op_kI32Gt_S = 0x4A,
    vm_op_kI32Gt_U = 0x4B,
    vm_op_kI32Le_S = 0x4C,
    vm_op_kI32Le_U = 0x4D,
    vm_op_kI32Ge_S = 0x4E,
    vm_op_kI32Ge_U = 0x4F,
    vm_op_kI64Eqz = 0x50,
    vm_op_kI64Eq = 0x51,
    vm_op_kI64Ne = 0x52,
    vm_op_kI64Lt_S = 0x53,
    vm_op_kI64Lt_U = 0x54,
    vm_op_kI64Gt_S = 0x55,
    vm_op_kI64Gt_U = 0x56,
    vm_op_kI64Le_S = 0x57,
    vm_op_kI64Le_U = 0x58,
    vm_op_kI64Ge_S = 0x59,
    vm_op_kI64Ge_U = 0x5A,
    vm_op_kF32Eq = 0x5B,
    vm_op_kF32Ne = 0x5C,
    vm_op_kF32Lt = 0x5D,
    vm_op_kF32Gt = 0x5E,
    vm_op_kF32Le = 0x5F,
    vm_op_kF32Ge = 0x60,
    vm_op_kF64Eq = 0x61,
    vm_op_kF64Ne = 0x62,
    vm_op_kF64Lt = 0x63,
    vm_op_kF64Gt = 0x64,
    vm_op_kF64Le = 0x65,
    vm_op_kF64Ge = 0x66,
    vm_op_kI32Clz = 0x67,
    vm_op_kI32Ctz = 0x68,
    vm_op_kI32Popcnt = 0x69,
    vm_op_kI32Add = 0x6A,
    vm_op_kI32Sub = 0x6B,
    vm_op_kI32Mul = 0x6C,
    vm_op_kI32Div_S = 0x6D,
    vm_op_kI32Div_U = 0x6E,
    vm_op_kI32Rem_S = 0x6F,
    vm_op_kI32Rem_U = 0x70,
    vm_op_kI32And = 0x71,
    vm_op_kI32Or = 0x72,
    vm_op_kI32Xor = 0x73,
    vm_op_kI32Shl = 0x74,
    vm_op_kI32Shr_S = 0x75,
    vm_op_kI32Shr_U = 0x76,
    vm_op_kI32Rotl = 0x77,
    vm_op_kI32Rotr = 0x78,
    vm_op_kI64Clz = 0x79,
    vm_op_kI64Ctz = 0x7A,
    vm_op_kI64Popcnt = 0x7B,
    vm_op_kI64Add = 0x7C,
    vm_op_kI64Sub = 0x7D,
    vm_op_kI64Mul = 0x7E,
    vm_op_kI64Div_S = 0x7F,
    vm_op_kI64Div_U = 0x80,
    vm_op_kI64Rem_S = 0x81,
    vm_op_kI64Rem_U = 0x82,
    vm_op_kI64And = 0x83,
    vm_op_kI64Or = 0x84,
    vm_op_kI64Xor = 0x85,
    vm_op_kI64Shl = 0x86,
    vm_op_kI64Shr_S = 0x87,
    vm_op_kI64Shr_U = 0x88,
    vm_op_kI64Rotl = 0x89,
    vm_op_kI64Rotr = 0x8A,
    vm_op_kF32Abs = 0x8B,
    vm_op_kF32Neg = 0x8C,
    vm_op_kF32Ceil = 0x8D,
    vm_op_kF32Floor = 0x8E,
    vm_op_kF32Trunc = 0x8F,
    vm_op_kF32Nearest = 0x90,
    vm_op_kF32Sqrt = 0x91,
    vm_op_kF32Add = 0x92,
    vm_op_kF32Sub = 0x93,
    vm_op_kF32Mul = 0x94,
    vm_op_kF32Div = 0x95,
    vm_op_kF32Min = 0x96,
    vm_op_kF32Max = 0x97,
    vm_op_kF32Copysign = 0x98,
    vm_op_kF64Abs = 0x99,
    vm_op_kF64Neg = 0x9A,
    vm_op_kF64Ceil = 0x9B,
    vm_op_kF64Floor = 0x9C,
    vm_op_kF64Trunc = 0x9D,
    vm_op_kF64Nearest = 0x9E,
    vm_op_kF64Sqrt = 0x9F,
    vm_op_kF64Add = 0xA0,
    vm_op_kF64Sub = 0xA1,
    vm_op_kF64Mul = 0xA2,
    vm_op_kF64Div = 0xA3,
    vm_op_kF64Min = 0xA4,
    vm_op_kF64Max = 0xA5,
    vm_op_kF64Copysign = 0xA6,
    vm_op_kI32WrapI64 = 0xA7,
    vm_op_kI32TruncF32_S = 0xA8,
    vm_op_kI32TruncF32_U = 0xA9,
    vm_op_kI32TruncF64_S = 0xAA,
    vm_op_kI32TruncF64_U = 0xAB,
    vm_op_kI64ExtendI32_S = 0xAC,
    vm_op_kI64ExtendI32_U = 0xAD,
    vm_op_kI64TruncF32_S = 0xAE,
    vm_op_kI64TruncF32_U = 0xAF,
    vm_op_kI64TruncF64_S = 0xB0,
    vm_op_kI64TruncF64_U = 0xB1,
    vm_op_kF32ConvertI32_S = 0xB2,
    vm_op_kF32ConvertI32_U = 0xB3,
    vm_op_kF32ConvertI64_S = 0xB4,
    vm_op_kF32ConvertI64_U = 0xB5,
    vm_op_kF32DemoteF64 = 0xB6,
    vm_op_kF64ConvertI32_S = 0xB7,
    vm_op_kF64ConvertI32_U = 0xB8,
    vm_op_kF64ConvertI64_S = 0xB9,
    vm_op_kF64ConvertI64_U = 0xBA,
    vm_op_kF64PromoteF32 = 0xBB,
    vm_op_kI32ReinterpretF32 = 0xBC,
    vm_op_kI64ReinterpretF64 = 0xBD,
    vm_op_kF32ReinterpretF32 = 0xBE,
    vm_op_kF64ReinterpretF64 = 0xBF,
    vm_op_kI32Extend8_S = 0xC0,
    vm_op_kI32Extend16_S = 0xC1,
    vm_op_kI64Extend8_S = 0xC2,
    vm_op_kI64Extend16_S = 0xC3,
    vm_op_kI64Extend32_S = 0xC4,
    
    vm_kOpSize = 0xC5
};

typedef vm_stack_t* (vm_op_exec_cb_t)(vm_stack_t* stack, void* immediates);

// #define i32 vm_kI32
// #define f32 vm_kF32
// #define i64 vm_kI64
// #define f64 vm_kF64

#define VM_OP_DEFINE_EXEC(OP, ...)                     \
vm_stack_t* _vm_exec_##OP##__(vm_stack_t* stack,       \
                          void* immediates) __VA_ARGS__

VM_OP_DEFINE_EXEC(kUnreachable);
VM_OP_DEFINE_EXEC(kNop);
VM_OP_DEFINE_EXEC(kBlock);
VM_OP_DEFINE_EXEC(kLoop);
VM_OP_DEFINE_EXEC(kIf);
VM_OP_DEFINE_EXEC(kElse);
VM_OP_DEFINE_EXEC(kEnd);
VM_OP_DEFINE_EXEC(kBr);
VM_OP_DEFINE_EXEC(kBrIf);
VM_OP_DEFINE_EXEC(kBrTable);
VM_OP_DEFINE_EXEC(kReturn);
VM_OP_DEFINE_EXEC(kCall);
VM_OP_DEFINE_EXEC(kCallIndirect);
VM_OP_DEFINE_EXEC(kDrop);
VM_OP_DEFINE_EXEC(kSelect);
VM_OP_DEFINE_EXEC(kSelectWithType);
VM_OP_DEFINE_EXEC(kLocalGet);
VM_OP_DEFINE_EXEC(kLocalSet);
VM_OP_DEFINE_EXEC(kLocalTee);
VM_OP_DEFINE_EXEC(kGlobalGet);
VM_OP_DEFINE_EXEC(kGlobalSet);
VM_OP_DEFINE_EXEC(kTableGet);
VM_OP_DEFINE_EXEC(kTableSet);
VM_OP_DEFINE_EXEC(kI32Load);
VM_OP_DEFINE_EXEC(kI64Load);
VM_OP_DEFINE_EXEC(kF32Load);
VM_OP_DEFINE_EXEC(kF64Load);
VM_OP_DEFINE_EXEC(kI32Load8_S);
VM_OP_DEFINE_EXEC(kI32Load8_U);
VM_OP_DEFINE_EXEC(kI32Load16_S);
VM_OP_DEFINE_EXEC(kI32Load16_U);
VM_OP_DEFINE_EXEC(kI64Load8_S);
VM_OP_DEFINE_EXEC(kI64Load8_U);
VM_OP_DEFINE_EXEC(kI64Load16_S);
VM_OP_DEFINE_EXEC(kI64Load16_U);
VM_OP_DEFINE_EXEC(kI64Load32_S);
VM_OP_DEFINE_EXEC(kI64Load32_U);
VM_OP_DEFINE_EXEC(kI32Store);
VM_OP_DEFINE_EXEC(kI64Store);
VM_OP_DEFINE_EXEC(kF32Store);
VM_OP_DEFINE_EXEC(kF64Store);
VM_OP_DEFINE_EXEC(kI32Store8);
VM_OP_DEFINE_EXEC(kI32Store16);
VM_OP_DEFINE_EXEC(kI64Store8);
VM_OP_DEFINE_EXEC(kI64Store16);
VM_OP_DEFINE_EXEC(kI64Store32);
VM_OP_DEFINE_EXEC(kMemorySize);
VM_OP_DEFINE_EXEC(kMemoryGrow);
VM_OP_DEFINE_EXEC(kI32Const);
VM_OP_DEFINE_EXEC(kI64Const);
VM_OP_DEFINE_EXEC(kF32Const);
VM_OP_DEFINE_EXEC(kF64Const);
VM_OP_DEFINE_EXEC(kI32Eqz);
VM_OP_DEFINE_EXEC(kI32Eq);
VM_OP_DEFINE_EXEC(kI32Ne);
VM_OP_DEFINE_EXEC(kI32Lt_S);
VM_OP_DEFINE_EXEC(kI32Lt_U);
VM_OP_DEFINE_EXEC(kI32Gt_S);
VM_OP_DEFINE_EXEC(kI32Gt_U);
VM_OP_DEFINE_EXEC(kI32Le_S);
VM_OP_DEFINE_EXEC(kI32Le_U);
VM_OP_DEFINE_EXEC(kI32Ge_S);
VM_OP_DEFINE_EXEC(kI32Ge_U);
VM_OP_DEFINE_EXEC(kI64Eqz);
VM_OP_DEFINE_EXEC(kI64Eq);
VM_OP_DEFINE_EXEC(kI64Ne);
VM_OP_DEFINE_EXEC(kI64Lt_S);
VM_OP_DEFINE_EXEC(kI64Lt_U);
VM_OP_DEFINE_EXEC(kI64Gt_S);
VM_OP_DEFINE_EXEC(kI64Gt_U);
VM_OP_DEFINE_EXEC(kI64Le_S);
VM_OP_DEFINE_EXEC(kI64Le_U);
VM_OP_DEFINE_EXEC(kI64Ge_S);
VM_OP_DEFINE_EXEC(kI64Ge_U);
VM_OP_DEFINE_EXEC(kF32Eq);
VM_OP_DEFINE_EXEC(kF32Ne);
VM_OP_DEFINE_EXEC(kF32Lt);
VM_OP_DEFINE_EXEC(kF32Gt);
VM_OP_DEFINE_EXEC(kF32Le);
VM_OP_DEFINE_EXEC(kF32Ge);
VM_OP_DEFINE_EXEC(kF64Eq);
VM_OP_DEFINE_EXEC(kF64Ne);
VM_OP_DEFINE_EXEC(kF64Lt);
VM_OP_DEFINE_EXEC(kF64Gt);
VM_OP_DEFINE_EXEC(kF64Le);
VM_OP_DEFINE_EXEC(kF64Ge);
VM_OP_DEFINE_EXEC(kI32Clz);
VM_OP_DEFINE_EXEC(kI32Ctz);
VM_OP_DEFINE_EXEC(kI32Popcnt);
VM_OP_DEFINE_EXEC(kI32Add);
VM_OP_DEFINE_EXEC(kI32Sub);
VM_OP_DEFINE_EXEC(kI32Mul);
VM_OP_DEFINE_EXEC(kI32Div_S);
VM_OP_DEFINE_EXEC(kI32Div_U);
VM_OP_DEFINE_EXEC(kI32Rem_S);
VM_OP_DEFINE_EXEC(kI32Rem_U);
VM_OP_DEFINE_EXEC(kI32And);
VM_OP_DEFINE_EXEC(kI32Or);
VM_OP_DEFINE_EXEC(kI32Xor);
VM_OP_DEFINE_EXEC(kI32Shl);
VM_OP_DEFINE_EXEC(kI32Shr_S);
VM_OP_DEFINE_EXEC(kI32Shr_U);
VM_OP_DEFINE_EXEC(kI32Rotl);
VM_OP_DEFINE_EXEC(kI32Rotr);
VM_OP_DEFINE_EXEC(kI64Clz);
VM_OP_DEFINE_EXEC(kI64Ctz);
VM_OP_DEFINE_EXEC(kI64Popcnt);
VM_OP_DEFINE_EXEC(kI64Add);
VM_OP_DEFINE_EXEC(kI64Sub);
VM_OP_DEFINE_EXEC(kI64Mul);
VM_OP_DEFINE_EXEC(kI64Div_S);
VM_OP_DEFINE_EXEC(kI64Div_U);
VM_OP_DEFINE_EXEC(kI64Rem_S);
VM_OP_DEFINE_EXEC(kI64Rem_U);
VM_OP_DEFINE_EXEC(kI64And);
VM_OP_DEFINE_EXEC(kI64Or);
VM_OP_DEFINE_EXEC(kI64Xor);
VM_OP_DEFINE_EXEC(kI64Shl);
VM_OP_DEFINE_EXEC(kI64Shr_S);
VM_OP_DEFINE_EXEC(kI64Shr_U);
VM_OP_DEFINE_EXEC(kI64Rotl);
VM_OP_DEFINE_EXEC(kI64Rotr);
VM_OP_DEFINE_EXEC(kF32Abs);
VM_OP_DEFINE_EXEC(kF32Neg);
VM_OP_DEFINE_EXEC(kF32Ceil);
VM_OP_DEFINE_EXEC(kF32Floor);
VM_OP_DEFINE_EXEC(kF32Trunc);
VM_OP_DEFINE_EXEC(kF32Nearest);
VM_OP_DEFINE_EXEC(kF32Sqrt);
VM_OP_DEFINE_EXEC(kF32Add);
VM_OP_DEFINE_EXEC(kF32Sub);
VM_OP_DEFINE_EXEC(kF32Mul);
VM_OP_DEFINE_EXEC(kF32Div);
VM_OP_DEFINE_EXEC(kF32Min);
VM_OP_DEFINE_EXEC(kF32Max);
VM_OP_DEFINE_EXEC(kF32Copysign);
VM_OP_DEFINE_EXEC(kF64Abs);
VM_OP_DEFINE_EXEC(kF64Neg);
VM_OP_DEFINE_EXEC(kF64Ceil);
VM_OP_DEFINE_EXEC(kF64Floor);
VM_OP_DEFINE_EXEC(kF64Trunc);
VM_OP_DEFINE_EXEC(kF64Nearest);
VM_OP_DEFINE_EXEC(kF64Sqrt);
VM_OP_DEFINE_EXEC(kF64Add);
VM_OP_DEFINE_EXEC(kF64Sub);
VM_OP_DEFINE_EXEC(kF64Mul);
VM_OP_DEFINE_EXEC(kF64Div);
VM_OP_DEFINE_EXEC(kF64Min);
VM_OP_DEFINE_EXEC(kF64Max);
VM_OP_DEFINE_EXEC(kF64Copysign);
VM_OP_DEFINE_EXEC(kI32WrapI64);
VM_OP_DEFINE_EXEC(kI32TruncF32_S);
VM_OP_DEFINE_EXEC(kI32TruncF32_U);
VM_OP_DEFINE_EXEC(kI32TruncF64_S);
VM_OP_DEFINE_EXEC(kI32TruncF64_U);
VM_OP_DEFINE_EXEC(kI64ExtendI32_S);
VM_OP_DEFINE_EXEC(kI64ExtendI32_U);
VM_OP_DEFINE_EXEC(kI64TruncF32_S);
VM_OP_DEFINE_EXEC(kI64TruncF32_U);
VM_OP_DEFINE_EXEC(kI64TruncF64_S);
VM_OP_DEFINE_EXEC(kI64TruncF64_U);
VM_OP_DEFINE_EXEC(kF32ConvertI32_S);
VM_OP_DEFINE_EXEC(kF32ConvertI32_U);
VM_OP_DEFINE_EXEC(kF32ConvertI64_S);
VM_OP_DEFINE_EXEC(kF32ConvertI64_U);
VM_OP_DEFINE_EXEC(kF32DemoteF64);
VM_OP_DEFINE_EXEC(kF64ConvertI32_S);
VM_OP_DEFINE_EXEC(kF64ConvertI32_U);
VM_OP_DEFINE_EXEC(kF64ConvertI64_S);
VM_OP_DEFINE_EXEC(kF64ConvertI64_U);
VM_OP_DEFINE_EXEC(kF64PromoteF32);
VM_OP_DEFINE_EXEC(kI32ReinterpretF32);
VM_OP_DEFINE_EXEC(kI64ReinterpretF64);
VM_OP_DEFINE_EXEC(kF32ReinterpretF32);
VM_OP_DEFINE_EXEC(kF64ReinterpretF64);
VM_OP_DEFINE_EXEC(kI32Extend8_S);
VM_OP_DEFINE_EXEC(kI32Extend16_S);
VM_OP_DEFINE_EXEC(kI64Extend8_S);
VM_OP_DEFINE_EXEC(kI64Extend16_S);
VM_OP_DEFINE_EXEC(kI64Extend32_S);


vm_op_exec_cb_t* vm_op_execs[vm_kOpSize] = { _vm_exec_kUnreachable__, _vm_exec_kNop__, _vm_exec_kBlock__, _vm_exec_kLoop__, _vm_exec_kIf__, _vm_exec_kElse__, _vm_exec_kUnreachable__, _vm_exec_kUnreachable__, _vm_exec_kUnreachable__, _vm_exec_kUnreachable__, _vm_exec_kUnreachable__, _vm_exec_kEnd__, _vm_exec_kBr__, _vm_exec_kBrIf__, _vm_exec_kBrTable__, _vm_exec_kReturn__, _vm_exec_kCall__, _vm_exec_kCallIndirect__, _vm_exec_kUnreachable__, _vm_exec_kUnreachable__, _vm_exec_kUnreachable__, _vm_exec_kUnreachable__, _vm_exec_kUnreachable__, _vm_exec_kUnreachable__, _vm_exec_kUnreachable__, _vm_exec_kUnreachable__, _vm_exec_kDrop__, _vm_exec_kSelect__, _vm_exec_kSelectWithType__, _vm_exec_kUnreachable__, _vm_exec_kUnreachable__, _vm_exec_kUnreachable__, _vm_exec_kLocalGet__, _vm_exec_kLocalSet__, _vm_exec_kLocalTee__, _vm_exec_kGlobalGet__, _vm_exec_kGlobalSet__, _vm_exec_kTableGet__, _vm_exec_kTableSet__, _vm_exec_kUnreachable__, _vm_exec_kI32Load__, _vm_exec_kI64Load__, _vm_exec_kF32Load__, _vm_exec_kF64Load__, _vm_exec_kI32Load8_S__, _vm_exec_kI32Load8_U__, _vm_exec_kI32Load16_S__, _vm_exec_kI32Load16_U__, _vm_exec_kI64Load8_S__, _vm_exec_kI64Load8_U__, _vm_exec_kI64Load16_S__, _vm_exec_kI64Load16_U__, _vm_exec_kI64Load32_S__, _vm_exec_kI64Load32_U__, _vm_exec_kI32Store__, _vm_exec_kI64Store__, _vm_exec_kF32Store__, _vm_exec_kF64Store__, _vm_exec_kI32Store8__, _vm_exec_kI32Store16__, _vm_exec_kI64Store8__, _vm_exec_kI64Store16__, _vm_exec_kI64Store32__, _vm_exec_kMemorySize__, _vm_exec_kMemoryGrow__, _vm_exec_kI32Const__, _vm_exec_kI64Const__, _vm_exec_kF32Const__, _vm_exec_kF64Const__, _vm_exec_kI32Eqz__, _vm_exec_kI32Eq__, _vm_exec_kI32Ne__, _vm_exec_kI32Lt_S__, _vm_exec_kI32Lt_U__, _vm_exec_kI32Gt_S__, _vm_exec_kI32Gt_U__, _vm_exec_kI32Le_S__, _vm_exec_kI32Le_U__, _vm_exec_kI32Ge_S__, _vm_exec_kI32Ge_U__, _vm_exec_kI64Eqz__, _vm_exec_kI64Eq__, _vm_exec_kI64Ne__, _vm_exec_kI64Lt_S__, _vm_exec_kI64Lt_U__, _vm_exec_kI64Gt_S__, _vm_exec_kI64Gt_U__, _vm_exec_kI64Le_S__, _vm_exec_kI64Le_U__, _vm_exec_kI64Ge_S__, _vm_exec_kI64Ge_U__, _vm_exec_kF32Eq__, _vm_exec_kF32Ne__, _vm_exec_kF32Lt__, _vm_exec_kF32Gt__, _vm_exec_kF32Le__, _vm_exec_kF32Ge__, _vm_exec_kF64Eq__, _vm_exec_kF64Ne__, _vm_exec_kF64Lt__, _vm_exec_kF64Gt__, _vm_exec_kF64Le__, _vm_exec_kF64Ge__, _vm_exec_kI32Clz__, _vm_exec_kI32Ctz__, _vm_exec_kI32Popcnt__, _vm_exec_kI32Add__, _vm_exec_kI32Sub__, _vm_exec_kI32Mul__, _vm_exec_kI32Div_S__, _vm_exec_kI32Div_U__, _vm_exec_kI32Rem_S__, _vm_exec_kI32Rem_U__, _vm_exec_kI32And__, _vm_exec_kI32Or__, _vm_exec_kI32Xor__, _vm_exec_kI32Shl__, _vm_exec_kI32Shr_S__, _vm_exec_kI32Shr_U__, _vm_exec_kI32Rotl__, _vm_exec_kI32Rotr__, _vm_exec_kI64Clz__, _vm_exec_kI64Ctz__, _vm_exec_kI64Popcnt__, _vm_exec_kI64Add__, _vm_exec_kI64Sub__, _vm_exec_kI64Mul__, _vm_exec_kI64Div_S__, _vm_exec_kI64Div_U__, _vm_exec_kI64Rem_S__, _vm_exec_kI64Rem_U__, _vm_exec_kI64And__, _vm_exec_kI64Or__, _vm_exec_kI64Xor__, _vm_exec_kI64Shl__, _vm_exec_kI64Shr_S__, _vm_exec_kI64Shr_U__, _vm_exec_kI64Rotl__, _vm_exec_kI64Rotr__, _vm_exec_kF32Abs__, _vm_exec_kF32Neg__, _vm_exec_kF32Ceil__, _vm_exec_kF32Floor__, _vm_exec_kF32Trunc__, _vm_exec_kF32Nearest__, _vm_exec_kF32Sqrt__, _vm_exec_kF32Add__, _vm_exec_kF32Sub__, _vm_exec_kF32Mul__, _vm_exec_kF32Div__, _vm_exec_kF32Min__, _vm_exec_kF32Max__, _vm_exec_kF32Copysign__, _vm_exec_kF64Abs__, _vm_exec_kF64Neg__, _vm_exec_kF64Ceil__, _vm_exec_kF64Floor__, _vm_exec_kF64Trunc__, _vm_exec_kF64Nearest__, _vm_exec_kF64Sqrt__, _vm_exec_kF64Add__, _vm_exec_kF64Sub__, _vm_exec_kF64Mul__, _vm_exec_kF64Div__, _vm_exec_kF64Min__, _vm_exec_kF64Max__, _vm_exec_kF64Copysign__, _vm_exec_kI32WrapI64__, _vm_exec_kI32TruncF32_S__, _vm_exec_kI32TruncF32_U__, _vm_exec_kI32TruncF64_S__, _vm_exec_kI32TruncF64_U__, _vm_exec_kI64ExtendI32_S__, _vm_exec_kI64ExtendI32_U__, _vm_exec_kI64TruncF32_S__, _vm_exec_kI64TruncF32_U__, _vm_exec_kI64TruncF64_S__, _vm_exec_kI64TruncF64_U__, _vm_exec_kF32ConvertI32_S__, _vm_exec_kF32ConvertI32_U__, _vm_exec_kF32ConvertI64_S__, _vm_exec_kF32ConvertI64_U__, _vm_exec_kF32DemoteF64__, _vm_exec_kF64ConvertI32_S__, _vm_exec_kF64ConvertI32_U__, _vm_exec_kF64ConvertI64_S__, _vm_exec_kF64ConvertI64_U__, _vm_exec_kF64PromoteF32__, _vm_exec_kI32ReinterpretF32__, _vm_exec_kI64ReinterpretF64__, _vm_exec_kF32ReinterpretF32__, _vm_exec_kF64ReinterpretF64__, _vm_exec_kI32Extend8_S__, _vm_exec_kI32Extend16_S__, _vm_exec_kI64Extend8_S__, _vm_exec_kI64Extend16_S__, _vm_exec_kI64Extend32_S__ };


// #undef i32
// #undef f32
// #undef i64
// #undef f64