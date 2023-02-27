#pragma once

#include <cstdint>

struct GraphicConfig {
  uint32_t width;
  uint32_t height;

  explicit GraphicConfig(uint32_t width = 960, uint32_t height = 540)
      : width(width), height(height) {}
};