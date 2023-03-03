#pragma once

namespace kplge {
namespace kplgltf {

enum class PrimitiveMode {
  POINTS = 0,
  LINES = 1,
  LINE_LOOP = 2,
  LINE_STRIP = 3,
  TRIANGLES = 4,
  TRIANGLE_STRIP = 5,
  TRIANGLE_FAN = 6,
};

enum class ComponentType {
  OTHER_TYPE,
  BYTE = 5120,
  UNSIGNED_BYTE = 5121,
  SHORT = 5122,
  UNSIGNED_SHORT = 5123,

  UNSIGNED_INT = 5125,
  FLOAT = 5126,
};

enum class AccessorType {
  OTHER_TYPE,
  SCALAR,
  VEC2,
  VEC3,
  VEC4,
  MAT2,
  MAT3,
  MAT4,
};

enum class BufferViewTarget {
  OTHER_TARGET,
  ARRAY_BUFFER = 34962,
  ELEMENT_ARRAY_BUFFER = 34963,
};

}  // namespace kplgltf
}  // namespace kplge