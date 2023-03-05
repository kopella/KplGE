#pragma once

#include <vector>

#include "scene-object.h"

namespace kplge {
enum class IndexDataType {
  I8,
  I16,
  I32,
};

enum class VertexDataType {
  VEC2F,
  VEC3F,
  VEC4F,
  VEC2D,
  VEC3D,
  VEC4D,
};

enum class VertexAttribute {
  POSITION,
  NORMAL,
  TEXCOORD,
  TANGENT,
};

enum class PrimitiveMode {
  POINTS = 0,
  LINES = 1,
  LINE_LOOP = 2,
  LINE_STRIP = 3,
  TRIANGLES = 4,
  TRIANGLE_STRIP = 5,
  TRIANGLE_FAN = 6,
};

class IndexArray {
 private:
  IndexDataType dataType_;
  std::vector<unsigned char> data_;

 public:
  IndexArray(IndexDataType dataType) : dataType_(dataType) {}
};

class VertexArray {
 private:
  VertexAttribute attribute_;
  VertexDataType dataType_;
  std::vector<unsigned char> data_;

 public:
  VertexArray(VertexAttribute attribute, VertexDataType dataType)
      : attribute_(attribute), dataType_(dataType) {}
};

class SceneMesh : public SceneObject {
 public:
  SceneMesh(){};
  SceneMesh(PrimitiveMode mode) : primitiveMode_(mode) {}

 private:
  std::vector<IndexArray> indexArraies_;
  std::vector<VertexArray> vertexArraies_;
  PrimitiveMode primitiveMode_;
};
}  // namespace kplge