// © Copyright Davio-2002

#include <chip8_opcode_dispatcher.hpp>
#include <array>

namespace {
    // Stub
    constexpr void OP_NULL(Ref<EMULATOR::Chip8>) noexcept {
    }

    // Secondary tables
    constexpr auto make_table0() {
        std::array<DISPATCHER::OpFunc, 0x10> t{};
        t.fill(OP_NULL);
        t[0x0] = OPCODES::OpCode_00E0;
        t[0xE] = OPCODES::OpCode_00EE;
        return t;
    }

    constexpr auto make_table8() {
        std::array<DISPATCHER::OpFunc, 0x10> t{};
        t.fill(OP_NULL);
        t[0x0] = OPCODES::OpCode_8XY0;
        t[0x1] = OPCODES::OpCode_8XY1;
        t[0x2] = OPCODES::OpCode_8XY2;
        t[0x3] = OPCODES::OpCode_8XY3;
        t[0x4] = OPCODES::OpCode_8XY4;
        t[0x5] = OPCODES::OpCode_8XY5;
        t[0x6] = OPCODES::OpCode_8XY6;
        t[0x7] = OPCODES::OpCode_8XY7;
        t[0xE] = OPCODES::OpCode_8XYE;
        return t;
    }

    constexpr auto make_tableE() {
        std::array<DISPATCHER::OpFunc, 0x10> t{};
        t.fill(OP_NULL);
        t[0x1] = OPCODES::OpCode_EXA1;
        t[0xE] = OPCODES::OpCode_EX9E;
        return t;
    }

    constexpr auto make_tableF() {
        std::array<DISPATCHER::OpFunc, 0x65 + 1> t{};
        t.fill(OP_NULL);
        t[0x07] = OPCODES::OpCode_FX07;
        t[0x0A] = OPCODES::OpCode_FX0A;
        t[0x15] = OPCODES::OpCode_FX15;
        t[0x18] = OPCODES::OpCode_FX18;
        t[0x1E] = OPCODES::OpCode_FX1E;
        t[0x29] = OPCODES::OpCode_FX29;
        t[0x33] = OPCODES::OpCode_FX33;
        t[0x55] = OPCODES::OpCode_FX55;
        t[0x65] = OPCODES::OpCode_FX65;
        return t;
    }

    // constexpr table initialization
    constexpr auto table0 = make_table0();
    constexpr auto table8 = make_table8();
    constexpr auto tableE = make_tableE();
    constexpr auto tableF = make_tableF();

    // Main table
    constexpr std::array<DISPATCHER::OpFunc, 16> mainTable = {
        // 0x0
        [](Ref<EMULATOR::Chip8> chip8) { table0[chip8.get_opcode() & 0x000Fu](chip8); },
        OPCODES::OpCode_1NNN,
        OPCODES::OpCode_2NNN,
        OPCODES::OpCode_3XKK,
        OPCODES::OpCode_4XKK,
        OPCODES::OpCode_5XY0,
        OPCODES::OpCode_6XKK,
        OPCODES::OpCode_7XKK,
        // 0x8
        [](Ref<EMULATOR::Chip8> chip8) { table8[chip8.get_opcode() & 0x000Fu](chip8); },
        OPCODES::OpCode_9XY0,
        OPCODES::OpCode_ANNN,
        OPCODES::OpCode_BNNN,
        OPCODES::OpCode_CXKK,
        OPCODES::OpCode_DXYN,
        // 0xE
        [](Ref<EMULATOR::Chip8> chip8) { tableE[chip8.get_opcode() & 0x000Fu](chip8); },
        // 0xF
        [](Ref<EMULATOR::Chip8> chip8) { tableF[chip8.get_opcode() & 0x00FFu](chip8); }
    };
} // anonymous namespace

namespace DISPATCHER {
    void execute_opcode(Ref<EMULATOR::Chip8> chip8) {
        const auto opcode = chip8.get_opcode();
        const auto index = (opcode & 0xF000u) >> 12; // NOT confuse with `I` register
        mainTable[index](chip8);
    }
} // namespace DISPATCH
