#include "gltf-constants.h"

namespace kplge {
namespace kplgltf {
std::ostream& operator<<(std::ostream& out, PrimitiveMode& mode) {
  switch (mode) {
    case PrimitiveMode::POINTS:
      out << "POINTS";
      break;
    case PrimitiveMode::LINES:
      out << "LINES";
      break;
    case PrimitiveMode::LINE_LOOP:
      out << "LINE_LOOP";
      break;
    case PrimitiveMode::LINE_STRIP:
      out << "LINE_STRIP";
      break;
    case PrimitiveMode::TRIANGLES:
      out << "TRIANGLES";
      break;
    case PrimitiveMode::TRIANGLE_STRIP:
      out << "TRIANGLE_STRIP";
      break;
    case PrimitiveMode::TRIANGLE_FAN:
      out << "TRIANGLE_FAN";
      break;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, ComponentType& type) {
  switch (type) {
    case ComponentType::OTHER_TYPE:
      out << "OTHER_TYPE";
      break;
    case ComponentType::BYTE:
      out << "BYTE";
      break;
    case ComponentType::UNSIGNED_BYTE:
      out << "UNSIGNED_BYTE";
      break;
    case ComponentType::SHORT:
      out << "SHORT";
      break;
    case ComponentType::UNSIGNED_SHORT:
      out << "UNSIGNED_SHORT";
      break;
    case ComponentType::UNSIGNED_INT:
      out << "UNSIGNED_INT";
      break;
    case ComponentType::FLOAT:
      out << "FLOAT";
      break;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, AccessorType& type) {
  switch (type) {
    case AccessorType::OTHER_TYPE:
      out << "OTHER_TYPE";
      break;
    case AccessorType::SCALAR:
      out << "SCALAR";
      break;
    case AccessorType::VEC2:
      out << "VEC2";
      break;
    case AccessorType::VEC3:
      out << "VEC3";
      break;
    case AccessorType::VEC4:
      out << "VEC4";
      break;
    case AccessorType::MAT2:
      out << "MAT2";
      break;
    case AccessorType::MAT3:
      out << "MAT3";
      break;
    case AccessorType::MAT4:
      out << "MAT4";
      break;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, BufferViewTarget& target) {
  switch (target) {
    case BufferViewTarget::OTHER_TARGET:
      out << "OTHER_TARGET";
      break;
    case BufferViewTarget::ARRAY_BUFFER:
      out << "ARRAY_BUFFER";
      break;
    case BufferViewTarget::ELEMENT_ARRAY_BUFFER:
      out << "ELEMENT_ARRAY_BUFFER";
      break;
  }
  return out;
}

static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(
    unsigned char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  const char* base64_chars =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz"
      "0123456789+/";

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] =
          ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] =
          ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for (i = 0; (i < 4); i++) ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 3; j++) char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] =
        ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] =
        ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

    for (j = 0; (j < i + 1); j++) ret += base64_chars[char_array_4[j]];

    while ((i++ < 3)) ret += '=';
  }

  return ret;
}

std::string base64_decode(std::string const& encoded_string) {
  int in_len = static_cast<int>(encoded_string.size());
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  const std::string base64_chars =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz"
      "0123456789+/";

  while (in_len-- && (encoded_string[in_] != '=') &&
         is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_];
    in_++;
    if (i == 4) {
      for (i = 0; i < 4; i++)
        char_array_4[i] =
            static_cast<unsigned char>(base64_chars.find(char_array_4[i]));

      char_array_3[0] =
          (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] =
          ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++) ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j < 4; j++) char_array_4[j] = 0;

    for (j = 0; j < 4; j++)
      char_array_4[j] =
          static_cast<unsigned char>(base64_chars.find(char_array_4[j]));

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] =
        ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}
}  // namespace kplgltf
}  // namespace kplge