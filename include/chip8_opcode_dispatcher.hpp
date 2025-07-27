// © Copyright Davio-2002

#pragma once

#include <chip-8.hpp>
#include <chip8_instructions.hpp>

namespace DISPATCHER {

    using OpFunc = void(*)(Ref<EMULATOR::Chip8> chip8);

    void execute_opcode(Ref<EMULATOR::Chip8> chip8);

} // namespace DISPATCHER