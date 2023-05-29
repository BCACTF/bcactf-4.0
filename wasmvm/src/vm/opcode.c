#include <stdio.h>

#include "vm/value.h"
#include "vm/stack.h"
#include "vm/opcode.h"

VM_OP_DEFINE_EXEC(kUnreachable, {

    return stack;
});
VM_OP_DEFINE_EXEC(kNop, {

    return stack;
}); 
VM_OP_DEFINE_EXEC(kBlock, {

    return stack;
});
VM_OP_DEFINE_EXEC(kLoop, {

    return stack;
});
VM_OP_DEFINE_EXEC(kIf, {

    return stack;
});
VM_OP_DEFINE_EXEC(kElse, {

    return stack;
});
VM_OP_DEFINE_EXEC(kEnd, {

    return stack;
});
VM_OP_DEFINE_EXEC(kBr, {

    return stack;
});
VM_OP_DEFINE_EXEC(kBrIf, {

    return stack;
});
VM_OP_DEFINE_EXEC(kBrTable, {

    return stack;
});
VM_OP_DEFINE_EXEC(kReturn, {

    return stack;
});
VM_OP_DEFINE_EXEC(kCall, {

    return stack;
});
VM_OP_DEFINE_EXEC(kCallIndirect, {

    return stack;
});
VM_OP_DEFINE_EXEC(kDrop, {

    return stack;
});
VM_OP_DEFINE_EXEC(kSelect, {

    return stack;
});
VM_OP_DEFINE_EXEC(kSelectWithType, {

    return stack;
});
VM_OP_DEFINE_EXEC(kLocalGet, {

    return stack;
});
VM_OP_DEFINE_EXEC(kLocalSet, {

    return stack;
});
VM_OP_DEFINE_EXEC(kLocalTee, {

    return stack;
});
VM_OP_DEFINE_EXEC(kGlobalGet, {

    return stack;
});
VM_OP_DEFINE_EXEC(kGlobalSet, {

    return stack;
});
VM_OP_DEFINE_EXEC(kTableGet, {

    return stack;
});
VM_OP_DEFINE_EXEC(kTableSet, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Load, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Load, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Load, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Load, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Load8_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Load8_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Load16_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Load16_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Load8_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Load8_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Load16_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Load16_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Load32_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Load32_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Store, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Store, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Store, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Store, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Store8, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Store16, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Store8, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Store16, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Store32, {

    return stack;
});
VM_OP_DEFINE_EXEC(kMemorySize, {

    return stack;
});
VM_OP_DEFINE_EXEC(kMemoryGrow, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Const, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Const, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Const, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Const, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Eqz, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Eq, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Ne, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Lt_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Lt_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Gt_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Gt_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Le_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Le_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Ge_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Ge_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Eqz, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Eq, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Ne, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Lt_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Lt_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Gt_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Gt_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Le_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Le_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Ge_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Ge_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Eq, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Ne, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Lt, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Gt, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Le, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Ge, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Eq, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Ne, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Lt, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Gt, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Le, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Ge, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Clz, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Ctz, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Popcnt, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Add, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Sub, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Mul, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Div_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Div_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Rem_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Rem_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32And, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Or, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Xor, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Shl, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Shr_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Shr_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Rotl, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Rotr, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Clz, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Ctz, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Popcnt, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Add, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Sub, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Mul, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Div_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Div_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Rem_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Rem_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64And, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Or, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Xor, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Shl, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Shr_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Shr_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Rotl, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Rotr, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Abs, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Neg, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Ceil, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Floor, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Trunc, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Nearest, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Sqrt, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Add, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Sub, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Mul, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Div, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Min, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Max, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32Copysign, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Abs, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Neg, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Ceil, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Floor, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Trunc, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Nearest, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Sqrt, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Add, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Sub, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Mul, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Div, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Min, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Max, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64Copysign, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32WrapI64, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32TruncF32_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32TruncF32_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32TruncF64_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32TruncF64_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64ExtendI32_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64ExtendI32_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64TruncF32_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64TruncF32_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64TruncF64_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64TruncF64_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32ConvertI32_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32ConvertI32_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32ConvertI64_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32ConvertI64_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32DemoteF64, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64ConvertI32_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64ConvertI32_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64ConvertI64_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64ConvertI64_U, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64PromoteF32, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32ReinterpretF32, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64ReinterpretF64, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF32ReinterpretF32, {

    return stack;
});
VM_OP_DEFINE_EXEC(kF64ReinterpretF64, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Extend8_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI32Extend16_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Extend8_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Extend16_S, {

    return stack;
});
VM_OP_DEFINE_EXEC(kI64Extend32_S, {

    return stack;
});