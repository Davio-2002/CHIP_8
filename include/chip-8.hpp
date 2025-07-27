// © Copyright Davio-2002

#pragma once

#include <constants.hpp>
#include <array>
#include <random>

namespace EMULATOR {
    class Chip8 {
    public:
        explicit Chip8() noexcept;

        //// Main methods
        void load_rom(const char *filename);

        void emulate_cycle();

        //// Operations With Core Components
        void clear_screen();

        void jump_to(u16 address);

        void push_stack(u16 address);

        void pop_stack();

        void return_from_subroutine();

        void advance_pc();

        void rewind_pc();

        void set_register_I(u16 address);

        uchar get_random_byte();

        void set_delay_timer(u8 value);

        void set_sound_timer(u8 value);

        //// Getters

        [[nodiscard]] u8 get_sp() const;

        [[nodiscard]] u16 get_opcode() const;

        [[nodiscard]] u16 get_pc() const;

        [[nodiscard]] u16 get_register_I() const;

        [[nodiscard]] u8 get_delay_timer() const;

        [[nodiscard]] Ref<std::array<u8, NUMBER_OF_REGISTERS> > get_registers();

        [[nodiscard]] Ref< std::uniform_int_distribution<u8> > get_rand_byte();

        [[nodiscard]] Ref< std::array<u8, MEMORY_SIZE> > get_memory();

        [[nodiscard]] Ref<std::array<u32, SCREEN_WIDTH * SCREEN_HEIGHT> > get_video();

        [[nodiscard]] Ref<std::array<u8, NUMBER_OF_KEYS> > get_keyboard();

        [[nodiscard]] ConstRef<std::array<u16, STACK_LEVEL_SIZE> > get_stack() const;

        //// Helpers

        // Helpers to extract parts of opcode
        [[nodiscard]] uint8_t get_Vx() const noexcept { return (opcode & 0x0F00u) >> 8u; }
        [[nodiscard]] uint8_t get_Vy() const noexcept { return (opcode & 0x00F0u) >> 4u; }
        [[nodiscard]] uint16_t get_NNN() const noexcept { return opcode & 0x0FFFu; }
        [[nodiscard]] uint8_t get_KK() const noexcept { return opcode & 0x00FFu; }
        [[nodiscard]] uint8_t get_N() const noexcept { return opcode & 0x000Fu; }

    private:
        /**
         * The Chip 8 has 15 8-bit general purpose registers named V0,V1 up to VE.
         * The 16th register is used for the ‘carry flag.’
         */
        std::array<u8, NUMBER_OF_REGISTERS> registers{};

        /**
         * The Chip 8 has 4K memory in total (4096 bytes)
         */
        std::array<u8, MEMORY_SIZE> memory{};

        /**
         * The graphics of the Chip 8 are black and white, and the screen has a total of 2048 pixels (64 x 32).
         * This can easily be implemented using an array that holds the pixel state (1 or 0):
         */
        std::array<u32, SCREEN_WIDTH * SCREEN_HEIGHT> video{};

        /**
         * The Chip 8 has a HEX-based keypad (from 0x0 to 0xF)
         */
        std::array<u8, NUMBER_OF_KEYS> keyboard{};

        /**
         * The system has 16 levels of stack, and to remember which level of the stack is used, we need to implement a stack pointer (sp).
         */
        std::array<u16, STACK_LEVEL_SIZE> stack{}; // 16-level program stack

        u16 index{};
        u16 pc{}; // program counter

        /**
         * The Chip 8 has 35 opcodes which are all two bytes long.
         */
        u16 opcode{};

        u8 sp{}; // stack pointer

        /**
         * Interrupts and hardware registers.
         * The Chip 8 has none, but there are two timer registers that count at 60 Hz.
         * When set above zero, they will count down to zero.
         */
        u8 delayTimer{};
        u8 soundTimer{};

        std::default_random_engine randGen;
        std::uniform_int_distribution<u8> randByte;
    };
}
