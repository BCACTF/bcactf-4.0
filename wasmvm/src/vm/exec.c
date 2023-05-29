#include <vm/exec.h>

#include <vm/opcode.h>

uint32_t vu32(uint8_t** bytes) {
    uint32_t out = 0;
    uint32_t i = 0;
    while (*bytes[0] & 0x80) {
        out |= (*bytes++[0] & 0x7F) << i;
        i += 7;
    }
    out |= (*bytes++[0] & 0x7F) << i;

    return out;
}


vm_stack_t* vm_execute(vm_stack_t* stack, uint8_t* in_bytes) {
    uint8_t* bytes = in_bytes;
    while (1) {
        enum vm_opcode op = (enum vm_opcode) bytes[0];

        int immediates[2];

        switch (op) {
            case vm_op_kI32Store:
            case vm_op_kI64Store:
            case vm_op_kF32Store:
            case vm_op_kF64Store:
            case vm_op_kI32Store8:
            case vm_op_kI32Store16:
            case vm_op_kI64Store8:
            case vm_op_kI64Store16:
            case vm_op_kI64Store32: {
                immediates[0] = vu32(&bytes);
                immediates[1] = vu32(&bytes);
                break;
            }
            default: break;
        }

        if (op == vm_op_kEnd) return stack;

        if (op > vm_kOpSize) op = vm_op_kUnreachable;
        stack = vm_op_execs[op](stack, immediates);
    }
}