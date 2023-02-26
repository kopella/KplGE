#pragma once
#include <array>
#include <string>

namespace kplge {
class Guid {
 private:
  std::array<unsigned char, 16> bytes_;

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

  std::string to_str() const;

  friend std::ostream& operator<<(std::ostream& out, const Guid& guid);
};
Guid generate_guid();
}  // namespace kplge