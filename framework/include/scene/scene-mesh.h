#pragma once

#include <vcruntime.h>
#include <ostream>
#include <vector>

#include "scene-type.h"
#include "scene-loader.h"
#include "scene-object.h"

namespace kplge {

class IndexArray {
 public:
  size_t count_;

 private:
  DataType dataType_;
  std::vector<unsigned char> data_;

 public:
  IndexArray(DataType dataType) : dataType_(dataType) {}

  std::vector<unsigned char>& GetData() { return data_; }

  friend std::ostream& operator<<(std::ostream& out, IndexArray& array) {
    out << " - "
        << "Count: " << array.count_ << std::endl;
    out << " - "
        << "Data Type: " << array.dataType_ << std::endl;
    return out;
  }
};

class VertexArray {
 public:
  PrimitiveMode primitiveMode_;
  VertexAttribute attribute_;
  size_t count_;

 private:
  DataType dataType_;
  std::vector<unsigned char> data_;

 public:
  VertexArray(DataType dataType) : dataType_(dataType) {}

  std::vector<unsigned char>& GetData() { return data_; }

  friend std::ostream& operator<<(std::ostream& out, VertexArray& array) {
    out << " - "
        << "------" << std::endl;
    out << " - "
        << "Primitive mode: " << array.primitiveMode_ << std::endl;
    out << " - "
        << "Attribute: " << array.attribute_ << std::endl;
    out << " - "
        << "Count: " << array.count_ << std::endl;
    out << " - "
        << "Data Type: " << array.dataType_ << std::endl;
    return out;
  }
};

class SceneMesh : public SceneObject {
 private:
  std::vector<IndexArray> indexArraies_;
  std::vector<VertexArray> vertexArraies_;

 public:
  SceneMesh(){};

  SceneMesh(kplgltf::Mesh mesh, kplgltf::GLtfContainer& gLtfContainer);

  friend std::ostream& operator<<(std::ostream& out, SceneMesh& mesh) {
    out << "Index arraies count: " << mesh.indexArraies_.size() << std::endl;
    for (auto& indexArray : mesh.indexArraies_) {
      out << indexArray;
    }
    out << "Vertex arraies count: " << mesh.vertexArraies_.size() << std::endl;
    for (auto& vertexArray : mesh.vertexArraies_) {
      out << vertexArray;
    }
    return out;
  }
};
}  // namespace kplge