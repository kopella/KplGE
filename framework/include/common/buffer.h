#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <memory>
#include <vector>

namespace kplge {
class Buffer {
 public:
  std::vector<unsigned char> data;

 public:
  unsigned char* get_data_pointer() {
    return reinterpret_cast<unsigned char*>(&data.at(0));
  }
  size_t get_data_size() const { return data.size(); };

  void set_data_by_pointer(unsigned char* p_data, size_t size) {
    std::vector<unsigned char> tmp(p_data, p_data + size);
    std::swap(data, tmp);
  }
};
}  // namespace kplge