#pragma once

#include <cstdint>

struct GraphicConfig {
  uint32_t width_;
  uint32_t height_;

  explicit GraphicConfig(uint32_t width = 960, uint32_t height = 540)
      : width_(width), height_(height) {}
};