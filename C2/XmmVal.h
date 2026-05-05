#pragma once
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;
struct alignas(16) XmmVal {
public:
  union {
    int8_t m_I8[16];
    int16_t m_I16[8];
    int32_t m_I32[4];
    int64_t m_I64[2];
    uint8_t m_U8[16];
    uint16_t m_U16[8];
    uint32_t m_U32[4];
    uint64_t m_U64[2];
  };

  string ToStringI16() {

    string s = "";
    for (int8_t i = 0; i < 8; i++) {
      s += to_string(m_I16[i]) + " | ";
    }

    return s;
  }

  string ToStringU16() {

    string s = "";
    for (int8_t i = 0; i < 8; i++) {
      s += to_string(m_U16[i]) + " | ";
    }

    return s;
  }

  string ToStringI32() {

    string s = "";
    for (int8_t i = 0; i < 4; i++) {

      s += to_string(m_I32[i]) + " | ";
    }

    return s;
  }

  string ToStringI64() {

    string s = "";
    for (int8_t i = 0; i < 2; i++) {

      s += to_string(m_I64[i]) + " | ";
    }

    return s;
  }

  string ToStringX16() {

    string s = "";
    for (int8_t i = 0; i < 8; i++) {

      s += to_string(m_U16[i]) + " | ";
    }

    return s;
  }
};
