// © Copyright Davio-2002

#pragma once

#include <type_aliases.hpp>

constexpr auto TITLE = "CHIP-8 Emulator";


// Chip-8 configuration
constexpr u16 SCREEN_WIDTH = 64;
constexpr u16 SCREEN_HEIGHT = 32;
constexpr u16 MEMORY_SIZE = 4096;
constexpr u8 STACK_LEVEL_SIZE = 16;
constexpr u8 NUMBER_OF_REGISTERS = 16;
constexpr u8 NUMBER_OF_KEYS = 16;
constexpr u8 NUMBER_OF_FONTS = 16;

// Addresses
constexpr u16 START_ADDRESS = 0x200;
constexpr u16 FONTSET_START_ADDRESS = 0x50;
constexpr u16 INSTRUCTION_SIZE = 2;

// Fonts
constexpr u8 FONT_BYTE_LENGTH = 5;
constexpr u8 FONTSET_LENGTH = NUMBER_OF_FONTS * FONT_BYTE_LENGTH;
