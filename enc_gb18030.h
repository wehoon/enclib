#pragma once

#include "enc_common.h"

namespace enc {

class GB18030 {
 public:
  static int GetNextWordByteLen(const char* s, int len) {
    if (len <= 0) return -1;
    if (isStrEnd(*s)) return -1;
    if (isASCII(*s)) return 1;

    if (!isFirstByte(*s)) return -1;
    if (isDoubleSecondByte(*(s + 1)) && len >= 2) return 2;
    if (isFourSecondByte(*(s + 1)) && isFirstByte(*(s + 2)) && isFourSecondByte(*(s + 3)) &&
        len >= 4)
      return 4;

    return -1;
  }

 private:
  static bool isFirstByte(byte_t b) { return 0x81 <= b && b <= 0xFE; }
  static bool isDoubleSecondByte(byte_t b) { return 0x40 <= b && b <= 0xFE && b != 0x7F; }
  static bool isFourSecondByte(byte_t b) { return 0x30 <= b && b <= 0x39; }
};

}  // namespace enc