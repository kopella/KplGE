#pragma once
#include <array>
#include <string>

namespace kplge {

class Guid {
 public:
  Guid() : bytes_{} {}
  Guid(const Guid& source) : bytes_(source.bytes_) {}
  Guid operator=(const Guid& source) {
    this->bytes_ = source.bytes_;
    return *this;
  }
  Guid(const std::array<unsigned char, 16>& bytes) {
    this->bytes_ = std::move(bytes);
  }

  std::string to_str() const {
    {
      char guid_cstr[39];
      snprintf(
          guid_cstr, sizeof(guid_cstr),
          "{%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%"
          "02x}",
          bytes_[0], bytes_[1], bytes_[2], bytes_[3], bytes_[4], bytes_[5],
          bytes_[6], bytes_[7], bytes_[8], bytes_[9], bytes_[10], bytes_[11],
          bytes_[12], bytes_[13], bytes_[14], bytes_[15]);
      return std::string{guid_cstr};
    }
  }

 private:
  std::array<unsigned char, 16> bytes_;

  friend std::ostream& operator<<(std::ostream& out, const Guid& guid) {
    {
      out << guid.to_str();
      return out;
    }
  }
};

Guid generate_guid();
}  // namespace kplge