#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <memory>

namespace kplge {
class Buffer {
 private:
  unsigned char* p_date_{};
  size_t sz_size_{};

 public:
  Buffer() = default;
  explicit Buffer(size_t size) : sz_size_(size) {
    p_date_ = reinterpret_cast<unsigned char*>(new unsigned char[size]);
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

  unsigned char* get_data() { return p_date_; };
  size_t get_data_size() const { return sz_size_; };

  void set_data(unsigned char* data, size_t size) {
    if (p_date_ != nullptr) {
      delete[] p_date_;
    }
    p_date_ = data;
    sz_size_ = size;
  }
};
}  // namespace kplge