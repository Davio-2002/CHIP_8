// © Copyright Davio-2002

#include <chip8_instructions.hpp>
#include <chip-8.hpp>
#include <constants.hpp>

void OPCODES::OpCode_00E0(Ref<EMULATOR::Chip8> chip8) {
    chip8.clear_screen();
}

void OPCODES::OpCode_00EE(Ref<EMULATOR::Chip8> chip8) {
    chip8.pop_stack();
    chip8.return_from_subroutine();
}

void OPCODES::OpCode_1NNN(Ref<EMULATOR::Chip8> chip8) {
    const u16 address = chip8.get_NNN();

    chip8.jump_to(address);
}

void OPCODES::OpCode_2NNN(Ref<EMULATOR::Chip8> chip8) {
    const u16 address = chip8.get_NNN();
    chip8.push_stack(chip8.get_pc());

    chip8.jump_to(address);
}

void OPCODES::OpCode_3XKK(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 byte = chip8.get_KK();

    const auto& registers = chip8.get_registers();
    if (registers[Vx] == byte) {
        chip8.advance_pc();
    }
}

void OPCODES::OpCode_4XKK(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 byte = chip8.get_KK();

    const auto& registers = chip8.get_registers();
    if (registers[Vx] != byte) {
        chip8.advance_pc();
    }
}

void OPCODES::OpCode_5XY0(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 Vy = chip8.get_Vy();

    const auto& registers = chip8.get_registers();
    if (registers[Vx] == registers[Vy]) {
        chip8.advance_pc();
    }
}

void OPCODES::OpCode_6XKK(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 byte = chip8.get_KK();

    auto& registers = chip8.get_registers();
    registers[Vx] = byte;
}

void OPCODES::OpCode_7XKK(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 byte = chip8.get_KK();

    auto& registers = chip8.get_registers();
    registers[Vx] += byte;
}

void OPCODES::OpCode_8XY0(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 Vy = chip8.get_Vy();

    auto& registers = chip8.get_registers();
    registers[Vx] = registers[Vy];
}

void OPCODES::OpCode_8XY1(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 Vy = chip8.get_Vy();

    auto& registers = chip8.get_registers();
    registers[Vx] |= registers[Vy];
}

void OPCODES::OpCode_8XY2(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 Vy = chip8.get_Vy();

    auto& registers = chip8.get_registers();
    registers[Vx] &= registers[Vy];
}

void OPCODES::OpCode_8XY3(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 Vy = chip8.get_Vy();

    auto& registers = chip8.get_registers();
    registers[Vx] ^= registers[Vy];
}

void OPCODES::OpCode_8XY4(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 Vy = chip8.get_Vy();

    auto& registers = chip8.get_registers();
    const u16 sum = registers[Vx] + registers[Vy];

    if (sum > 255) {
        registers[0xF] = 1;
    } else {
        registers[0xF] = 0;
    }

    registers[Vx] = sum & 0xFFU;
}

void OPCODES::OpCode_8XY5(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 Vy = chip8.get_Vy();

    auto& registers = chip8.get_registers();
    if (registers[Vx] > registers[Vy])
    {
        registers[0xF] = 1;
    }
    else
    {
        registers[0xF] = 0;
    }

    registers[Vx] -= registers[Vy];
}

void OPCODES::OpCode_8XY6(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();

    auto& registers = chip8.get_registers();
    registers[0xF] = registers[Vx] & 0x1;
    registers[Vx] >>= 1;
}

void OPCODES::OpCode_8XY7(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 Vy = chip8.get_Vy();

    auto& registers = chip8.get_registers();
    if (registers[Vy] > registers[Vx])
    {
        registers[0xF] = 1;
    }
    else
    {
        registers[0xF] = 0;
    }

    registers[Vx] = registers[Vy] - registers[Vx];
}

void OPCODES::OpCode_8XYE(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();

    auto& registers = chip8.get_registers();

    registers[0xF] = (registers[Vx] & 0x80) >> 7U;
    registers[Vx] <<= 1;
}

void OPCODES::OpCode_9XY0(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 Vy = chip8.get_Vy();

    const auto& registers = chip8.get_registers();
    if (registers[Vx] != registers[Vy]) {
        chip8.advance_pc();
    }
}

void OPCODES::OpCode_ANNN(Ref<EMULATOR::Chip8> chip8) {
    const u16 address = chip8.get_NNN();

    chip8.set_register_I( address );
}

void OPCODES::OpCode_BNNN(Ref<EMULATOR::Chip8> chip8) {
    const u16 address = chip8.get_NNN();

    const auto& registers = chip8.get_registers();
    chip8.jump_to(registers[0] + address);
}

void OPCODES::OpCode_CXKK(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 byte = chip8.get_KK();

    auto& registers = chip8.get_registers();

    registers[Vx] = chip8.get_random_byte() & byte;
}

void OPCODES::OpCode_DXYN(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const u8 Vy = chip8.get_Vy();

    const u8 height = chip8.get_N();

    auto& registers = chip8.get_registers();
    const auto& memory = chip8.get_memory();
    const u8 x_pos = registers[Vx] % SCREEN_WIDTH;
    const u8 y_pos = registers[Vy] % SCREEN_HEIGHT;

    registers[0xF] = 0;

    for (u8 row = 0; row < height; ++row) {
        const u8 spriteByte = memory[chip8.get_register_I() + row];
        for (u8 col = 0; col < 8; ++col) {
            const u8 spritePixel = spriteByte & (0x80 >> col);
            const auto screenPixel = &chip8.get_video()[(y_pos + row) * SCREEN_WIDTH + (x_pos + col)];

            if (spritePixel)
            {
                // Screen pixel also on - collision
                if (*screenPixel == 0xFFFFFFFF)
                {
                    registers[0xF] = 1;
                }

                // Effectively XOR with the sprite pixel
                *screenPixel ^= 0xFFFFFFFF;
            }
        }
    }
}

void OPCODES::OpCode_EX9E(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const auto& registers = chip8.get_registers();
    const u8 key = registers[Vx];
    const auto& keypad = chip8.get_keyboard();

    if (keypad[key]) {
        chip8.advance_pc();
    }
}

void OPCODES::OpCode_EXA1(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const auto& registers = chip8.get_registers();
    const auto& keypad = chip8.get_keyboard();
    const u8 key = registers[Vx];

    if (!keypad[key]) {
        chip8.advance_pc();
    }
}

void OPCODES::OpCode_FX07(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    auto& registers = chip8.get_registers();
    const auto& delay_timer = chip8.get_delay_timer();

    registers[Vx] = delay_timer;
}

void OPCODES::OpCode_FX0A(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    auto& registers = chip8.get_registers();
    const auto& keypad = chip8.get_keyboard();

    bool key_pressed = false;
    for (uint8_t i = 0; i < 16; ++i) {
        if (keypad[i]) {
            registers[Vx] = i;
            key_pressed = true;
            break;
        }
    }

    if (!key_pressed) {
         chip8.rewind_pc();
    }
}

void OPCODES::OpCode_FX15(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const auto& registers = chip8.get_registers();

    chip8.set_delay_timer(registers[Vx]);
}

void OPCODES::OpCode_FX18(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const auto& registers = chip8.get_registers();

    chip8.set_sound_timer(registers[Vx]);
}

void OPCODES::OpCode_FX1E(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const auto& registers = chip8.get_registers();

    chip8.set_register_I(registers[Vx]);
}

void OPCODES::OpCode_FX29(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const auto& registers = chip8.get_registers();

    const u8 digit = registers[Vx];
    chip8.set_register_I(FONTSET_START_ADDRESS + 5 * digit);
}

void OPCODES::OpCode_FX33(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const auto& registers = chip8.get_registers();

    const u8 value = registers[Vx];
    auto& memory = chip8.get_memory();
    const auto I = chip8.get_register_I();


    memory[I] = value / 100;
    memory[I + 1] = value / 10 % 10;
    memory[I + 2] = value % 10;
}

void OPCODES::OpCode_FX55(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    const auto& registers = chip8.get_registers();
    auto& memory = chip8.get_memory();
    const auto I = chip8.get_register_I();

    for (u8 i = 0; i <= Vx; ++i) {
        memory[I + i] = registers[i];
    }
}

void OPCODES::OpCode_FX65(Ref<EMULATOR::Chip8> chip8) {
    const u8 Vx = chip8.get_Vx();
    auto& registers = chip8.get_registers();
    const auto& memory = chip8.get_memory();
    const auto I = chip8.get_register_I();

    for (u8 i = 0; i <= Vx; ++i) {
        registers[i] = memory[I + i];
    }
}
