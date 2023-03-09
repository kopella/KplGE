#include <ostream>
#include "scene-loader.h"

namespace kplge {
enum class VertexDataType {
  VEC2F,
  VEC3F,
  VEC4F,
  VEC2D,
  VEC3D,
  VEC4D,
};

std::ostream& operator<<(std::ostream& out, VertexDataType& attribute);

enum class IndexDataType {
  I8,
  I16,
  I32,
};

std::ostream& operator<<(std::ostream& out, IndexDataType& attribute);

enum class VertexAttribute {
  POSITION,
  NORMAL,
  TEXCOORD,
  TANGENT,
};

std::ostream& operator<<(std::ostream& out, VertexAttribute& attribute);

enum class PrimitiveMode {
  POINTS = 0,
  LINES = 1,
  LINE_LOOP = 2,
  LINE_STRIP = 3,
  TRIANGLES = 4,
  TRIANGLE_STRIP = 5,
  TRIANGLE_FAN = 6,
};

std::ostream& operator<<(std::ostream& out, PrimitiveMode& mode);

IndexDataType GetIndexDataTypeFromGltf(kplgltf::Accessor accessor);
VertexDataType GetVertexDataTypeFromGltf(kplgltf::Accessor accessor);

PrimitiveMode GetPrimitiveModeFromGltf(kplgltf::PrimitiveMode type);

}  // namespace kplge