#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <memory>

namespace kplge {
class Buffer {
 public:
  Buffer() = default;
  explicit Buffer(size_t size) : sz_size_(size) {
    p_date_ = reinterpret_cast<uint8_t*>(new uint8_t[size]);
  }

  Buffer(const Buffer& rhs) = delete;
  Buffer& operator=(const Buffer& rhs) = delete;

  Buffer(Buffer&& rhs) noexcept {
    p_date_ = rhs.p_date_;
    sz_size_ = rhs.sz_size_;
    rhs.p_date_ = nullptr;
    rhs.sz_size_ = 0;
  }
  Buffer& operator=(Buffer&& rhs) noexcept {
    delete[] p_date_;
    p_date_ = rhs.p_date_;
    sz_size_ = rhs.sz_size_;
    rhs.p_date_ = nullptr;
    rhs.sz_size_ = 0;
    return *this;
  }

  ~Buffer() {
    if (p_date_ != nullptr) {
      delete[] p_date_;
    }
  }

  uint8_t* get_data() { return p_date_; };
  size_t get_data_size() const { return sz_size_; };
  
  void set_data(uint8_t* data, size_t size) {
    if (p_date_ != nullptr) {
      delete[] p_date_;
    }
    p_date_ = data;
    sz_size_ = size;
  }

 private:
  uint8_t* p_date_{};
  size_t sz_size_{};
};
}  // namespace kplge