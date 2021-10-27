#pragma once

#include <cstring>
#include <string>
#include <vector>
#include "enc_gbk.h"
#include "enc_gb18030.h"
#include "enc_utf8.h"

namespace enc {

template <typename EncCore>
class Enc {
 public:
  static int GetWordCount(const char* s, int len) {
    const char* p = s;
    const char* end = p + len;
    int cnt = 0;
    while (p < end) {
      int word_byte = EncCore::GetNextWordByteLen(p, end - p);
      if (word_byte < 0) return -1;
      p += word_byte;
      ++cnt;
    }
    return cnt;
  }

  static int GetWordCount(const std::string& s) { return GetWordCount(s.data(), s.size()); }

  static int FindFirstOf(const std::string& str, const std::string& sub) {
    if (str.size() < sub.size()) return -1;

    const char* pStr = str.c_str();
    const char* pSub = sub.c_str();
    const char* pStrEnd = pStr + str.size();
    int sub_len = sub.size();

    while (pStr < pStrEnd) {
      if (memcmp(pStr, pSub, sub_len) == 0) {
        return (pStr - str.c_str());
      }
      int next_step = EncCore::GetNextWordByteLen(pStr, pStrEnd - pStr);
      if (next_step < 0) return -1;
      pStr = pStr + next_step;
    }

    return -1;
  }

  static int Split(const std::string& str, const std::string& sep, std::vector<std::string>& res) {
    const char* pStr = str.c_str();
    const char* pSep = sep.c_str();
    const char* pStrEnd = pStr + str.size();
    int sep_len = sep.size();
    if (sep_len == 0) {
      res.push_back(str);
      return 1;
    }
    size_t start_pos = 0;
    size_t end_pos = 0;
    while (pStr < pStrEnd) {
      if (memcmp(pStr, pSep, sep_len) == 0) {
        if (end_pos >= start_pos) {
          res.push_back(str.substr(start_pos, end_pos - start_pos));
        }
        pStr += sep_len;
        start_pos = end_pos + sep_len;
        end_pos = start_pos;
      } else {
        int next_byte = EncCore::GetNextWordByteLen(pStr, pStrEnd - pStr);
        if (next_byte < 0) return -1;
        pStr += next_byte;
        end_pos += next_byte;
      }
    }
    if (end_pos >= start_pos) {
      res.push_back(str.substr(start_pos, end_pos - start_pos));
    }
    return res.size();
  }

  static std::string SubStr(const std::string& str, size_t start_word_pos, size_t word_size) {
    int word_count = GetWordCount(str);
    if (start_word_pos >= word_count) return "";

    int cur_word_pos = 0;
    int sub_byte_len = 0;
    int end_word_pos = start_word_pos + word_size;
    const char* s = str.c_str();
    const char* start = s;
    const char* end = s + str.size();
    while (s < end) {
      if (cur_word_pos == start_word_pos) {
        start = s;
        sub_byte_len = 0;
        if (end_word_pos >= word_count) {
          return std::string(start, end - start);
        }
      }
      if (cur_word_pos == end_word_pos) {
        return std::string(start, sub_byte_len);
      }

      int next_byte = EncCore::GetNextWordByteLen(s, end - s);
      ++cur_word_pos;
      s += next_byte;
      if (cur_word_pos >= start_word_pos) {
        sub_byte_len += next_byte;
      }
    }
    return "";
  }

  static std::string IgnoreError(const std::string& str) {
    std::string res;
    const char* s = str.c_str();
    const char* end = s + str.size();
    while (s < end) {
      int next_byte = EncCore::GetNextWordByteLen(s, end - s);
      while (next_byte < 0 && s < end) {
        ++s;
        next_byte = EncCore::GetNextWordByteLen(s, end - s);
      }
      if (next_byte > 0) {
        res.insert(res.size(), s, next_byte);
        s += next_byte;
      } else {
        ++s;
      }
    }
    return res;
  }

  static std::string RemoveAll(const std::string& str, const std::string& sub) {
    if (sub.size() > str.size()) return str;
    const char* s = str.c_str();
    const char* end = s + str.size();

    std::string res;
    while (s < end) {
      if (memcmp(s, sub.c_str(), sub.size()) == 0) {
        s += sub.size();
        continue;
      }
      int next_byte = EncCore::GetNextWordByteLen(s, end - s);
      if (next_byte > 0) {
        res.insert(res.size(), s, next_byte);
        s += next_byte;
      } else {
        ++s;
      }
    }
    return res;
  }

  static int GetNextWordByteLen(const char* s, int len) {
    return EncCore::GetNextWordByteLen(s, len);
  }
};

}  // namespace enc
