// © Copyright Davio-2002

#pragma once
#include <type_aliases.hpp>

namespace EMULATOR {
    class Chip8;
}

/*
    CHIP-8 instruction format:

    I (index)      - index register
    nnn (addr)     - 12-bit address (lowest 12 bits of the instruction)
    n (nibble)     - 4-bit value (lowest 4 bits of the instruction)
    x              - 4-bit value (lower 4 bits of the high byte)
    y              - 4-bit value (upper 4 bits of the low byte)
    kk (byte)      - 8-bit immediate value (lowest 8 bits of the instruction)

    Reference: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
*/

namespace OPCODES {

    /* 00E0 - CLS: Clear the display */
    void OpCode_00E0(Ref<EMULATOR::Chip8> chip8);

    /* 00EE - RET: Return from a subroutine.
       Sets PC to the address on top of the stack, then decrements SP. */
    void OpCode_00EE(Ref<EMULATOR::Chip8> chip8);

    /* 1nnn - JP addr: Jump to address nnn */
    void OpCode_1NNN(Ref<EMULATOR::Chip8> chip8);

    /* 2nnn - CALL addr: Call subroutine at nnn */
    void OpCode_2NNN(Ref<EMULATOR::Chip8> chip8);

    /* 3xkk - SE Vx, byte: Skip next instruction if Vx == kk */
    void OpCode_3XKK(Ref<EMULATOR::Chip8> chip8);

    /* 4xkk - SNE Vx, byte: Skip next instruction if Vx != kk */
    void OpCode_4XKK(Ref<EMULATOR::Chip8> chip8);

    /* 5xy0 - SE Vx, Vy: Skip next instruction if Vx == Vy */
    void OpCode_5XY0(Ref<EMULATOR::Chip8> chip8);

    /* 6xkk - LD Vx, byte: Set Vx = kk */
    void OpCode_6XKK(Ref<EMULATOR::Chip8> chip8);

    /* 7xkk - ADD Vx, byte: Set Vx = Vx + kk (no carry) */
    void OpCode_7XKK(Ref<EMULATOR::Chip8> chip8);

    /* 8xy0 - LD Vx, Vy: Set Vx = Vy */
    void OpCode_8XY0(Ref<EMULATOR::Chip8> chip8);

    /* 8xy1 - OR Vx, Vy: Set Vx = Vx OR Vy */
    void OpCode_8XY1(Ref<EMULATOR::Chip8> chip8);

    /* 8xy2 - AND Vx, Vy: Set Vx = Vx AND Vy */
    void OpCode_8XY2(Ref<EMULATOR::Chip8> chip8);

    /* 8xy3 - XOR Vx, Vy: Set Vx = Vx XOR Vy */
    void OpCode_8XY3(Ref<EMULATOR::Chip8> chip8);

    /* 8xy4 - ADD Vx, Vy: Set Vx = Vx + Vy. VF = carry */
    void OpCode_8XY4(Ref<EMULATOR::Chip8> chip8);

    /* 8xy5 - SUB Vx, Vy: Set Vx = Vx - Vy. VF = NOT borrow */
    void OpCode_8XY5(Ref<EMULATOR::Chip8> chip8);

    /* 8xy6 - SHR Vx {, Vy}: Set Vx = Vx >> 1. VF = least significant bit before shift */
    void OpCode_8XY6(Ref<EMULATOR::Chip8> chip8);

    /* 8xy7 - SUBN Vx, Vy: Set Vx = Vy - Vx. VF = NOT borrow */
    void OpCode_8XY7(Ref<EMULATOR::Chip8> chip8);

    /* 8xyE - SHL Vx {, Vy}: Set Vx = Vx << 1. VF = most significant bit before shift */
    void OpCode_8XYE(Ref<EMULATOR::Chip8> chip8);

    /* 9xy0 - SNE Vx, Vy: Skip next instruction if Vx != Vy */
    void OpCode_9XY0(Ref<EMULATOR::Chip8> chip8);

    /* Annn - LD I, addr: Set index register I = nnn */
    void OpCode_ANNN(Ref<EMULATOR::Chip8> chip8);

    /* Bnnn - JP V0, addr: Jump to address nnn + V0 */
    void OpCode_BNNN(Ref<EMULATOR::Chip8> chip8);

    /* Cxkk - RND Vx, byte: Set Vx = random byte AND kk */
    void OpCode_CXKK(Ref<EMULATOR::Chip8> chip8);

    /* Dxyn - DRW Vx, Vy, nibble: Display n-byte sprite at (Vx, Vy).
       Each set bit in sprite XORs the display pixels. VF = collision. */
    void OpCode_DXYN(Ref<EMULATOR::Chip8> chip8);

    /* Ex9E - SKP Vx: Skip next instruction if key Vx is pressed */
    void OpCode_EX9E(Ref<EMULATOR::Chip8> chip8);

    /* ExA1 - SKNP Vx: Skip next instruction if key Vx is NOT pressed */
    void OpCode_EXA1(Ref<EMULATOR::Chip8> chip8);

    /* Fx07 - LD Vx, DT: Set Vx = delay timer value */
    void OpCode_FX07(Ref<EMULATOR::Chip8> chip8);

    /* Fx0A - LD Vx, K: Wait for a key press, store key in Vx (execution stops) */
    void OpCode_FX0A(Ref<EMULATOR::Chip8> chip8);

    /* Fx15 - LD DT, Vx: Set delay timer = Vx */
    void OpCode_FX15(Ref<EMULATOR::Chip8> chip8);

    /* Fx18 - LD ST, Vx: Set sound timer = Vx */
    void OpCode_FX18(Ref<EMULATOR::Chip8> chip8);

    /* Fx1E - ADD I, Vx: Set I = I + Vx */
    void OpCode_FX1E(Ref<EMULATOR::Chip8> chip8);

    /* Fx29 - LD F, Vx: Set I to location of sprite for digit Vx */
    void OpCode_FX29(Ref<EMULATOR::Chip8> chip8);

    /* Fx33 - LD B, Vx: Store BCD of Vx at I, I+1, I+2 */
    void OpCode_FX33(Ref<EMULATOR::Chip8> chip8);

    /* Fx55 - LD [I], Vx: Store registers V0 through Vx in memory starting at I */
    void OpCode_FX55(Ref<EMULATOR::Chip8> chip8);

    /* Fx65 - LD Vx, [I]: Read registers V0 through Vx from memory starting at I */
    void OpCode_FX65(Ref<EMULATOR::Chip8> chip8);

} // namespace OPCODES
