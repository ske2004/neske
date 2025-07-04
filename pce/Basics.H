/* basic defns */
#pragma once

#include <cstdint>

using U0   = void;
using I8   = int8_t;
using U8   = uint8_t;
using I16  = int16_t;
using U16  = uint16_t;
using I32  = int32_t;
using U32  = uint32_t;
using I64  = int64_t;
using U64  = uint64_t;
using Uxx  = size_t;
using Ixx  = intptr_t;
using Bool = bool;

using CStr = const char*;

template<Uxx N>
constexpr Uxx Length(char const (&)[N])
{
  return N-1;
}