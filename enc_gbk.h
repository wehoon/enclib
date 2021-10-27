#pragma once

#include "enc_common.h"

namespace enc {

class GBK {
 public:
  static int GetNextWordByteLen(const char* s, int len) {
    if (len <= 0) return -1;
    if (isStrEnd(*s)) return -1;
    if (isASCII(*s)) return 1;

    if (!isFirstByte(*s)) return -1;
    if (isSecondByte(*(s + 1)) && len >= 2) return 2;

    return -1;
  }

 private:
  static bool isFirstByte(byte_t b) { return 0x81 <= b && b <= 0xFE; }
  static bool isSecondByte(byte_t b) { return 0x40 <= b && b <= 0xFE && b != 0x7F; }
};

}  // namespace enc
