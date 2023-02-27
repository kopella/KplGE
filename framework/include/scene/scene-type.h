#pragma once

#include <iostream>

namespace kplge {

enum class SceneObjectType {
  TYPE_INDEX,
  TYPE_VERTEX,
  TYPE_MESH,
  TYPE_MATERIAL,
};

std::ostream& operator<<(std::ostream& out, const SceneObjectType type);

enum class IndexDataType {
  INDEX_I8,
  INDEX_I16,
  INDEX_I32,
  INDEX_I64,
};

enum class VertexDataType {
  VERTEX_VEC2F,
  VERTEX_VEC3F,
  VERTEX_VEC4F,
  VERTEX_VEC2D,
  VERTEX_VEC3D,
  VERTEX_VEC4D,
};

enum class VertexAttribute {
  VERTEX_POSITION,
  VERTEX_NORMAL,
  VERTEX_TEXCOORD,
  VERTEX_TANGENT,
};

enum class PrimitiveType {
  PRIMITIVE_NONE,
};
}  // namespace kplge