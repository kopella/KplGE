#include "scene-object.h"
#include "scene-mesh.h"

#include <iostream>

#include "scene-type.h"

namespace kplge {
std::ostream& operator<<(std::ostream& out, const SceneObjectType type) {
  switch (type) {
    case SceneObjectType::MESH:
      out << "MESH";
      break;
    case SceneObjectType::NONE:
      out << "NONE";
      break;
  }
  return out;
}

SceneMesh::SceneMesh(kplgltf::Mesh mesh, kplgltf::GLtfContainer& gLtfContainer)
    : SceneObject(SceneObjectType::MESH) {
  for (auto& primitive : mesh.primitives) {
    kplgltf::Accessor indices_accessor =
        gLtfContainer.accessors[primitive.indices];
    kplgltf::BufferView indices_bufferView =
        gLtfContainer.bufferViews[indices_accessor.bufferView];

    IndexArray indexArray;
    auto pos = gLtfContainer.buffers[indices_bufferView.buffer].data.begin() +
               indices_bufferView.byteOffset;
    indexArray.data_.resize(indices_bufferView.byteLength);
    std::copy(
        pos, pos + indices_bufferView.byteLength, indexArray.data_.begin());
    this->indexArraies_.emplace_back(std::move(indexArray));

    for (auto& attribute : primitive.attributes) {
      kplgltf::Accessor attribute_accessor =
          gLtfContainer.accessors[attribute.second];
      kplgltf::BufferView attribute_bufferView =
          gLtfContainer.bufferViews[attribute_accessor.bufferView];

      VertexArray vertexArray;
      if (attribute.first.compare("POSITION") == 0)
        vertexArray.attribute_ = VertexAttribute::POSITION;
      if (attribute.first.compare("NORMAL") == 0)
        vertexArray.attribute_ = VertexAttribute::NORMAL;
      if (attribute.first.compare("TEXCOORD_0") == 0)
        vertexArray.attribute_ = VertexAttribute::TEXCOORD;

      auto pos =
          gLtfContainer.buffers[attribute_bufferView.buffer].data.begin() +
          attribute_bufferView.byteOffset;
      vertexArray.data_.resize(attribute_bufferView.byteLength);
      std::copy(
          pos, pos + attribute_bufferView.byteLength,
          vertexArray.data_.begin());
    }
  }
}
}  // namespace kplge