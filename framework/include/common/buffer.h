#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <memory>

namespace kplge {
class Buffer {
 public:
  Buffer() = default;
  explicit Buffer(size_t size) : sz_size(size) {
    p_date = reinterpret_cast<uint8_t*>(new uint8_t[size]);
  }

  Buffer(const Buffer& rhs) = delete;
  Buffer& operator=(const Buffer& rhs) = delete;

  Buffer(Buffer&& rhs) noexcept {
    p_date = rhs.p_date;
    sz_size = rhs.sz_size;
    rhs.p_date = nullptr;
    rhs.sz_size = 0;
  }
  Buffer& operator=(Buffer&& rhs) noexcept {
    delete[] p_date;
    p_date = rhs.p_date;
    sz_size = rhs.sz_size;
    rhs.p_date = nullptr;
    rhs.sz_size = 0;
    return *this;
  }

  ~Buffer() {
    if (p_date != nullptr) {
      delete[] p_date;
    }
  }

  uint8_t* get_data() { return p_date; };
  size_t get_data_size() const { return sz_size; };
  
  void set_data(uint8_t* data, size_t size) {
    if (p_date != nullptr) {
      delete[] p_date;
    }
    p_date = data;
    sz_size = size;
  }

 private:
  uint8_t* p_date{};
  size_t sz_size{};
};
}  // namespace kplge