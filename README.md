# enclib
编码字符串通用库

## API
以模板静态方法调用: *`Enc<EncCore>::Function()`*, 目前实现了`GB18030`和`UTF8`两个EncCore
- `enc::Enc<enc::UTF8>::Function()`
- `enc::Enc<enc::GB18030>::Function()`

### 主要方法
#### - int GetWordCount(const std::string& s)
获取实际字数, 错误返回-1

#### - int FindFirstOf(const std::string& str, const std::string& sub)
在str中查找第一次出现sub的位置, 未找到返回-1

#### - int Split(const std::string& str, const std::string& sep, std::vector<std::string>& res)
以sep切分字符串str，结果保存在res中，返回结果数量，错误返回-1

#### - std::string SubStr(const std::string& str, size_t start_word_pos, size_t word_size)
截取字符串str中从start_word_pos开始的word_size个字

#### - std::string RemoveAll(const std::string& str, const std::string& sub)
从str中删除所有sub子串

#### - std::string IgnoreError(const std::string& str)
忽略str中乱码字符，得到过滤后的合法字符串

## Usage
``` c++

#include <iostream>
#include <string>
#include <vector>
#include "enclib.h"

namespace std {
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  os << "[";
  for (size_t i = 0; i < v.size(); ++i) {
    if (i != 0) os << ", ";
    os << v[i];
  }
  os << "]";
  return os;
}
}  // namespace std

using ENC = enc::Enc<enc::UTF8>;

int main(int argc, char const* argv[]) {
  std::string str("&测试字符串1&&测试字符串2&");

  // word count
  int word_count = ENC::GetWordCount(str);
  std::cout << "word count: " << word_count << std::endl;

  // find
  std::string sub1("字符串");
  std::string sub2("字符集");
  int pos1 = ENC::FindFirstOf(str, sub1);
  int pos2 = ENC::FindFirstOf(str, sub2);
  std::cout << "find pos1: " << pos1 << std::endl;
  std::cout << "find pos2: " << pos2 << std::endl;

  // split
  std::string sep1("&");
  std::string sep2("字符");
  std::vector<std::string> vec1, vec2;
  ENC::Split(str, sep1, vec1);
  ENC::Split(str, sep2, vec2);
  std::cout << "split result1: " << vec1 << std::endl;
  std::cout << "split result2: " << vec2 << std::endl;

  // substr
  std::string substr1 = ENC::SubStr(str, 2, 5);
  std::string substr2 = ENC::SubStr(str, 17, 2);
  std::string substr3 = ENC::SubStr(str, 9, 10);
  std::cout << "substr1: " << substr1 << std::endl;
  std::cout << "substr2: " << substr2 << std::endl;
  std::cout << "substr3: " << substr3 << std::endl;

  // remove_all
  std::string rmsub1 = ENC::RemoveAll(str, "字符");
  std::string rmsub2 = ENC::RemoveAll(str, "&");
  std::cout << "rmsub1: " << rmsub1 << std::endl;
  std::cout << "rmsub2: " << rmsub2 << std::endl;

  return 0;
}

/* == Output ==
word count: 16
find pos1: 7
find pos2: -1
split result1: [, 测试字符串1, , 测试字符串2, ]
split result2: [&测试, 串1&&测试, 串2&]
substr1: 试字符串1
substr2: 
substr3: 测试字符串2&
rmsub1: &测试串1&&测试串2&
rmsub2: 测试字符串1测试字符串2
*/
```

## TODO
1. Unicode互转
2. Insert相关函数
