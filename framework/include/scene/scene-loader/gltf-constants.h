#pragma once

#include <ostream>
#include <vector>

namespace kplge {
namespace kplgltf {
using GltfId = unsigned int;
using GltfNum = float;
using GltfInt = int;
using Vector3Num = std::vector<GltfNum>;
using Vector4Num = std::vector<GltfNum>;
using Matrix4X4Num = std::vector<GltfNum>;

const GltfId INVALID_ID = -1;

const Vector4Num DEFAULT_ROTATION{0.0, 0.0, 0.0, 1.0};
const Vector3Num DEFAULT_SCALE{1.0, 1.0, 1.0};
const Vector3Num DEFAULT_TRANSLATION{0.0, 0.0, 0.0};
const Matrix4X4Num DEAFULA_MATRIX{1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                                  0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};

enum class PrimitiveMode : GltfId {
  POINTS = 0,
  LINES = 1,
  LINE_LOOP = 2,
  LINE_STRIP = 3,
  TRIANGLES = 4,
  TRIANGLE_STRIP = 5,
  TRIANGLE_FAN = 6,
};

std::ostream& operator<<(std::ostream& out, PrimitiveMode& mode);

enum class ComponentType {
  OTHER_TYPE,
  BYTE = 5120,
  UNSIGNED_BYTE = 5121,
  SHORT = 5122,
  UNSIGNED_SHORT = 5123,

  UNSIGNED_INT = 5125,
  FLOAT = 5126,
};

std::ostream& operator<<(std::ostream& out, ComponentType& type);

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

std::ostream& operator<<(std::ostream& out, AccessorType& type);

enum class BufferViewTarget {
  OTHER_TARGET,
  ARRAY_BUFFER = 34962,
  ELEMENT_ARRAY_BUFFER = 34963,
};

std::ostream& operator<<(std::ostream& out, BufferViewTarget& target);

}  // namespace kplgltf
}  // namespace kplge