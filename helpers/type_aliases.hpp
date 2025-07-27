// © Copyright Davio-2002

#pragma once

#include <cstdint>

// Signed integer types
using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

// Unsigned integer types
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using uchar = unsigned char;

// Floating-point types
using f32 = float;
using f64 = double;

// Size and pointer difference
using usize = std::size_t;
using isize = std::ptrdiff_t;

// Character types
using ch8 = char;
using ch16 = char16_t;
using ch32 = char32_t;

// Optional aliasing templates (if needed)
template<typename T>
using Ref = T &;

template<typename T>
using Ptr = T *;

template<typename T>
using ConstRef = const T &;

template<typename T>
using ConstPtr = const T *;
