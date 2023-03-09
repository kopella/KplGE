#pragma once

#include <vcruntime.h>
#include <iostream>
#include <vector>

#include "scene-type.h"
#include "scene-loader.h"
#include "scene-object.h"

namespace kplge {

class IndexArray {
 public:
  IndexDataType dataType_;
  size_t count_;
  size_t byteOffset_;
  size_t byteStride_;

 private:
  std::vector<unsigned char> data_;

 public:
  IndexArray(IndexDataType dataType) : dataType_(dataType) {}

  std::vector<unsigned char>& GetData() { return data_; }

  friend std::ostream& operator<<(std::ostream& out, IndexArray& array) {
    out << " - "
        << "Data Type: " << array.dataType_ << std::endl;
    out << " - "
        << "Count: " << array.count_ << std::endl;
    out << " - "
        << "ByteOffset: " << array.byteOffset_ << std::endl;
    out << " - "
        << "ByteStride: " << array.byteStride_ << std::endl;
    out << " - "
        << "Contents: ";
    for (auto val : array.data_) printf("\\x%.2x", val);
    out << std::endl;
    return out;
  }
};

class VertexArray {
 public:
  VertexAttribute attribute_;
  VertexDataType dataType_;
  size_t count_;
  size_t byteOffset_;
  size_t byteStride_;
  bool normalized_;

 private:
  std::vector<unsigned char> data_;

 public:
  VertexArray(VertexDataType dataType) : dataType_(dataType) {}

  std::vector<unsigned char>& GetData() { return data_; }

  friend std::ostream& operator<<(std::ostream& out, VertexArray& array) {
    out << " - "
        << "------" << std::endl;
    out << " - "
        << "Attribute: " << array.attribute_ << std::endl;
    out << " - "
        << "Data Type: " << array.dataType_ << std::endl;
    out << " - "
        << "Count: " << array.count_ << std::endl;
    out << " - "
        << "ByteOffset: " << array.byteOffset_ << std::endl;
    out << " - "
        << "ByteStride: " << array.byteStride_ << std::endl;
    out << " - "
        << "Normalized: " << array.normalized_ << std::endl;
    out << " - "
        << "Contents: ";
    for (auto val : array.data_) printf("\\x%.2x", val);
    out << std::endl;
    return out;
  }
};

class SceneMesh : public SceneObject {
 private:
  std::vector<IndexArray> indexArraies_;
  std::vector<VertexArray> vertexArraies_;

  PrimitiveMode primitiveMode_;

 public:
  SceneMesh(){};

  SceneMesh(kplgltf::Mesh mesh, const kplgltf::GLtfContainer& gLtfContainer);

  std::vector<IndexArray> GetIndexArraies() { return indexArraies_; }
  std::vector<VertexArray> GetVertexArraies() { return vertexArraies_; }

  PrimitiveMode GetPrimitiveMode() { return primitiveMode_; }

  friend std::ostream& operator<<(std::ostream& out, SceneMesh& mesh) {
    out << " - "
        << "Primitive mode: " << mesh.primitiveMode_ << std::endl;
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