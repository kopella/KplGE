#pragma once
#include <vector>

#include "scene-object.h"

namespace kplge {
class IndexArray {
 protected:
  const IndexDataType DataType_;

  const uint32_t MaterialIndex_;
  const size_t sz_RestartIndex_;

  const uint8_t* p_Data_;
  const size_t sz_Data_;

 public:
  explicit IndexArray(
      const IndexDataType data_type, const uint32_t material_index,
      const size_t sz_restart_index, const uint8_t* p_data,
      const size_t sz_data)
      : DataType_(data_type),
        MaterialIndex_(material_index),
        sz_RestartIndex_(sz_restart_index),
        p_Data_(p_data),
        sz_Data_(sz_data){};

  IndexArray(IndexArray& index) = delete;
  IndexArray(IndexArray&& index)
      : DataType_(index.DataType_),
        MaterialIndex_(index.MaterialIndex_),
        sz_RestartIndex_(index.sz_RestartIndex_),
        p_Data_(index.p_Data_),
        sz_Data_(index.sz_Data_) {
    index.p_Data_ = nullptr;
  };
  ~IndexArray() {
    if (p_Data_) delete[] p_Data_;
  }

  friend std::ostream& operator<<(std::ostream& out, const IndexArray index);
};

class VertexArray {
 protected:
  const VertexAttribute Attribute_;
  const VertexDataType DataType_;

  const uint32_t MorphIndex_;

  const uint8_t* p_Data_;
  const size_t sz_Data_;

 public:
  explicit VertexArray(
      const VertexAttribute attribute, const VertexDataType data_type,
      const uint32_t morph_index, const uint8_t* p_data, const size_t sz_data)
      : Attribute_(attribute),
        DataType_(data_type),
        MorphIndex_(morph_index),
        p_Data_(p_data),
        sz_Data_(sz_data){};

  VertexArray(VertexArray& vertex) = delete;
  VertexArray(VertexArray&& vertex)
      : Attribute_(vertex.Attribute_),
        DataType_(vertex.DataType_),
        MorphIndex_(vertex.MorphIndex_),
        p_Data_(vertex.p_Data_),
        sz_Data_(vertex.sz_Data_) {
    vertex.p_Data_ = nullptr;
  };
  ~VertexArray() {
    if (p_Data_) delete[] p_Data_;
  }

  friend std::ostream& operator<<(std::ostream& out, const VertexArray vertex);
};

class Mesh : public SceneObject {
 protected:
  std::vector<IndexArray> IndexArraies_;
  std::vector<VertexArray> VertexArraies_;

  PrimitiveType PrimitiveType_;
};
}  // namespace kplge