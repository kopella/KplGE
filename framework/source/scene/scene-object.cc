#include "scene-object.h"
#include <vcruntime.h>
#include "scene-mesh.h"

namespace kplge {
SceneMesh::SceneMesh(
    kplgltf::Mesh mesh, const kplgltf::GLtfContainer& gLtfContainer) {
  for (auto& primitive : mesh.primitives) {
    kplgltf::Accessor indices_accessor =
        gLtfContainer.accessors[primitive.indices];
    kplgltf::BufferView indices_bufferView =
        gLtfContainer.bufferViews[indices_accessor.bufferView];

    PrimitiveMode mode = static_cast<PrimitiveMode>(primitive.mode);

    this->primitiveMode_ = mode;

    IndexArray indexArray(GetIndexDataTypeFromGltf(indices_accessor));
    indexArray.count_ = indices_accessor.count;
    indexArray.byteOffset_ = indices_accessor.byteOffset;
    indexArray.byteStride_ = indices_bufferView.byteStride;
    auto pos = gLtfContainer.buffers[indices_bufferView.buffer].data.begin() +
               indices_bufferView.byteOffset;

    indexArray.GetData().resize(indices_bufferView.byteLength);
    std::copy(
        pos, pos + indices_bufferView.byteLength, indexArray.GetData().begin());
    this->indexArraies_.emplace_back(std::move(indexArray));

    for (auto& attribute : primitive.attributes) {
      kplgltf::Accessor attribute_accessor =
          gLtfContainer.accessors[attribute.second];
      kplgltf::BufferView attribute_bufferView =
          gLtfContainer.bufferViews[attribute_accessor.bufferView];

      VertexArray vertexArray(GetVertexDataTypeFromGltf(attribute_accessor));
      vertexArray.count_ = attribute_accessor.count;
      vertexArray.byteOffset_ = attribute_accessor.byteOffset;
      vertexArray.byteStride_ = attribute_bufferView.byteStride;
      vertexArray.normalized_ = attribute_accessor.normalized;
      if (attribute.first.compare("POSITION") == 0)
        vertexArray.attribute_ = VertexAttribute::POSITION;
      if (attribute.first.compare("NORMAL") == 0)
        vertexArray.attribute_ = VertexAttribute::NORMAL;
      if (attribute.first.compare("TEXCOORD_0") == 0)
        vertexArray.attribute_ = VertexAttribute::TEXCOORD;

      auto pos =
          gLtfContainer.buffers[attribute_bufferView.buffer].data.begin() +
          attribute_bufferView.byteOffset;

      vertexArray.GetData().resize(attribute_bufferView.byteLength);
      std::copy(
          pos, pos + attribute_bufferView.byteLength,
          vertexArray.GetData().begin());

      this->vertexArraies_.emplace_back(std::move(vertexArray));
    }
  }
}
}  // namespace kplge