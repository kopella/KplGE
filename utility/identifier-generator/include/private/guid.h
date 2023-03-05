#pragma once
#include <array>
#include <string>

namespace kplutl {
class Guid {
 private:
  std::array<unsigned char, 16> bytes_;

 public:
  Guid() { this->Generate(); }
  Guid(Guid& source) = default;
  Guid& operator=(Guid& source) = default;
  Guid(Guid&& source) = default;
  Guid& operator=(Guid&& source) = default;

  void Generate();

  std::string to_str() const;

  friend std::ostream& operator<<(std::ostream& out, const Guid& guid);
};

}  // namespace kplutl