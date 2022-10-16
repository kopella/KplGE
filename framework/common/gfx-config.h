#pragma once
#include <cstdint>

struct GraphicsConfiguration {
  uint32_t width;
  uint32_t height;

  explicit GraphicsConfiguration(uint32_t width = 960, uint32_t height = 540)
      : width(width), height(height) {}
};