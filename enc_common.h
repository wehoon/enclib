#pragma once

namespace enc {

typedef unsigned char byte_t;
typedef uint16_t ucs2_t;
typedef uint32_t ucs4_t;

inline bool isStrEnd(byte_t b) { return b == '\0'; }

inline bool isASCII(byte_t b) { return (0x00 <= b && b <= 0x7F); }

}