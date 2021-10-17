#pragma once

#include "enc_common.h"

namespace enc {

class UTF8 {
 public:
  static int GetNextWordByteLen(const char* s, int len) {
    if (len <= 0) return -1;
    if (isStrEnd(*s)) return -1;
    if (isASCII(*s)) return 1;

    int except_len = getExpectLenByFirst(*s);
    if (except_len < 0 || len < except_len) return -1;
    for (int i = 1; i < except_len; ++i) {
      if (!isValidOtherByte(*(s + i))) return -1;
    }
    return except_len;
  }

 private:
  static bool isFirstByte(byte_t b) { return 0xC0 <= b && b <= 0xFD; }

  static bool isValidOtherByte(byte_t b) { return 0x80 <= b && b <= 0xBF; }

  static int getExpectLenByFirst(byte_t b) {
    if (!isFirstByte(b)) return -1;
    if (b < 0xE0) return 2;
    if (b < 0xF0) return 3;
    if (b < 0xF8) return 4;
    if (b < 0xFC) return 5;
    if (b < 0xFE) return 6;
    return -1;
  }
};

}  // namespace enc