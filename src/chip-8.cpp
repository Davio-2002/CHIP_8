// © Copyright Davio-2002

#include <chip-8.hpp>
#include <chip8_opcode_dispatcher.hpp>
#include <fstream>
#include <vector>
#include <fonts.h>
#include <chrono>
#include <iostream>

namespace EMULATOR {
    Chip8::Chip8() noexcept: randGen(std::chrono::system_clock::now().time_since_epoch().count()) {
        pc = START_ADDRESS;

        std::ranges::copy(FONTS::fontset, memory.begin() + FONTSET_START_ADDRESS);

        randByte = std::uniform_int_distribution<u8>(0, 255U);
    }

/* Operations With Core Components */

    void Chip8::clear_screen() {
        std::ranges::fill(video, 0);
    }

    void Chip8::jump_to(const u16 address) {
        pc = address;
    }

    void Chip8::push_stack(const u16 address) {
        stack[sp] = address;
        ++sp;
    }

    void Chip8::pop_stack() {
        --sp;
    }

    void Chip8::return_from_subroutine() {
        pc = stack[sp];
    }

    void Chip8::advance_pc() {
        pc += INSTRUCTION_SIZE;
    }

    void Chip8::rewind_pc() {
        pc -= INSTRUCTION_SIZE;
    }

    void Chip8::set_register_I(const u16 address) {
        index = address;
    }

    uchar Chip8::get_random_byte() {
        return randByte(randGen);
    }

    void Chip8::set_delay_timer(const u8 value) {
        delayTimer = value;
    }

    void Chip8::set_sound_timer(const u8 value) {
        soundTimer = value;
    }

    /* End Operations With Core Components */


    /* Getters */

    //// Scalar types
    u16 Chip8::get_pc() const {
        return pc;
    }

    u16 Chip8::get_register_I() const {
        return index;
    }

    u8 Chip8::get_delay_timer() const {
        return delayTimer;
    }

    Ref<std::array<u8, NUMBER_OF_REGISTERS>> Chip8::get_registers() {
        return registers;
    }

    u8 Chip8::get_sp() const {
        return sp;
    }

    u16 Chip8::get_opcode() const {
        return opcode;
    }

    //// Big structures
    Ref<std::array<u32, SCREEN_WIDTH * SCREEN_HEIGHT> > Chip8::get_video() {
        return video;
    }

    Ref<std::array<u8, NUMBER_OF_KEYS>> Chip8::get_keyboard() {
        return keyboard;
    }

    ConstRef<std::array<u16, STACK_LEVEL_SIZE> > Chip8::get_stack() const {
        return stack;
    }

    Ref< std::uniform_int_distribution<u8> > Chip8::get_rand_byte() {
        return randByte;
    }

    Ref< std::array<u8, MEMORY_SIZE> > Chip8::get_memory() {
        return memory;
    }

    /* End Getters */

    bool Chip8::load_rom(const char *filename) {
        // Open the file as a stream of binary and move the file pointer to the end (.ate)
        std::ifstream file(filename, std::ios::binary | std::ios::ate);

        if (!file.is_open()) {
            std::cerr << "Failed to open ROM: " << filename << std::endl;
            return false;
        }

        // Get the size of the file and ensure it fits into memory
        const std::streampos fileSize = file.tellg();
        if (START_ADDRESS + fileSize > MEMORY_SIZE) {
            std::cerr << "ROM is too large to fit into memory (" << fileSize << " bytes)" << std::endl;
            return false;
        }

        std::vector<char> buffer(fileSize);

        // Go back to the beginning of the file and fill the buffer
        file.seekg(0, std::ios::beg);
        if (!file.read(buffer.data(), fileSize)) {
            std::cerr << "Failed to read ROM: " << filename << std::endl;
            return false;
        }
        file.close();

        // Copy buffer contents to memory
        std::copy(buffer.begin(), buffer.end(), memory.begin() + START_ADDRESS);
        return true;
    }

    void Chip8::emulate_cycle() {
        opcode = (memory[pc] << 8u) | memory[pc + 1];

        advance_pc();

        DISPATCHER::execute_opcode(*this);

        if (delayTimer > 0) {
            --delayTimer;
        }

        if (soundTimer > 0) {
            --soundTimer;
        }
    }
} // namespace EMULATOR
