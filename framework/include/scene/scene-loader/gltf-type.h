#pragma once

#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "gltf-constants.h"

namespace kplge {
namespace kplgltf {

struct Asset {
  std::string version{"2.0"};
  std::string copyright;
  std::string generator;

  friend std::ostream& operator<<(std::ostream& out, Asset& asset) {
    out << "version: " << asset.version << std::endl;
    if (!asset.generator.empty())
      out << "generator: " << asset.generator << std::endl;
    if (!asset.copyright.empty())
      out << "copyright: " << asset.copyright << std::endl;
    return out;
  }
};

struct Scene {
  std::string name;
  std::vector<GltfId> nodes;

  friend std::ostream& operator<<(std::ostream& out, Scene& scene) {
    out << "Scene: " << scene.name << std::endl;
    out << " - "
        << "nodes: "
        << "[ ";
    for (size_t i = 0; i < scene.nodes.size(); ++i) {
      out << scene.nodes[i] << (i != scene.nodes.size() - 1 ? ", " : "");
    }
    out << " ]" << std::endl;
    return out;
  }
};

struct Node {
  std::string name;
  std::vector<GltfId> children;
  GltfId mesh{INVALID_ID};
  GltfId camera{INVALID_ID};
  GltfId skin{INVALID_ID};
  Matrix4X4Num matrix;
  Vector3Num scale;
  Vector4Num rotation;
  Vector3Num translation;
  std::vector<GltfNum> weights;

  friend std::ostream& operator<<(std::ostream& out, Node& node) {
    out << "Node: " << node.name << std::endl;
    if (!node.children.empty()) {
      out << " - "
          << "Children: "
          << "[ ";
      for (size_t i = 0; i < node.children.size(); ++i) {
        out << node.children[i] << (i != node.children.size() - 1 ? ", " : "");
      }
      out << " ]" << std::endl;
    }

    if (node.mesh != INVALID_ID) {
      out << " - "
          << "mesh: " << node.mesh << std::endl;
    }

    if (node.camera != INVALID_ID) {
      out << " - "
          << "camera: " << node.camera << std::endl;
    }

    if (node.skin != INVALID_ID) {
      out << " - "
          << "skin: " << node.skin << std::endl;
    }

    if (!node.matrix.empty()) {
      out << " - "
          << "matrix: " << std::endl;
      for (size_t i = 0; i < 4; ++i) {
        out << "   "
            << "[ ";
        for (size_t j = 0; j < 4; ++j) {
          out << node.matrix[i * 4 + j] << (j != 3 ? ", " : "");
        }
        out << " ]" << std::endl;
      }
    } else {
      if (!node.rotation.empty()) {
        out << " - "
            << "rotation: "
            << "[ ";
        for (size_t i = 0; i < 4; ++i) {
          out << node.rotation[i] << (i != 3 ? ", " : "");
        }
        out << " ]" << std::endl;
      }

      if (!node.scale.empty()) {
        out << " - "
            << "scale: "
            << "[ ";
        for (size_t i = 0; i < 3; ++i) {
          out << node.scale[i] << (i != 2 ? ", " : "");
        }
        out << " ]" << std::endl;
      }

      if (!node.translation.empty()) {
        out << " - "
            << "translation: "
            << "[ ";
        for (size_t i = 0; i < 3; ++i) {
          out << node.translation[i] << (i != 2 ? ", " : "");
        }
        out << " ]" << std::endl;
      }
    }

    if (!node.weights.empty()) {
      out << " - "
          << "weights: "
          << "[ ";
      for (size_t i = 0; i < node.weights.size(); ++i) {
        out << node.weights[i] << (i != node.weights.size() - 1 ? ", " : "");
      }
      out << " ]" << std::endl;
    }
    return out;
  }
};

struct Primitive {
  std::map<std::string, GltfId> attributes;
  GltfId indices{INVALID_ID};
  GltfId material{INVALID_ID};
  PrimitiveMode mode{static_cast<PrimitiveMode>(4)};
  std::vector<std::map<std::string, GltfId>> targets;

  friend std::ostream& operator<<(std::ostream& out, Primitive& primitive) {
    out << " | "
        << " - "
        << "attributes: " << std::endl;
    for (auto& [key, value] : primitive.attributes) {
      out << " | "
          << " | "
          << " - " << key << ": " << value << std::endl;
    }

    if (primitive.indices != INVALID_ID) {
      out << " | "
          << " - "
          << "indices: ";
      out << primitive.indices << std::endl;
    }

    if (primitive.material != INVALID_ID) {
      out << " | "
          << " - "
          << "material: ";
      out << primitive.material << std::endl;
    }

    out << " | "
        << " - "
        << "mode: " << primitive.mode << std::endl;

    if (!primitive.targets.empty()) {
      out << " | "
          << " - "
          << "targets: " << std::endl;

      for (auto& target : primitive.targets) {
        out << " | "
            << " | "
            << " - "
            << "------" << std::endl;
        for (auto& [key, value] : target) {
          out << " | "
              << " | "
              << " - " << key << ": " << value << std::endl;
        }
      }
      out << " | "
          << " | "
          << " - "
          << "------" << std::endl;
    }
    return out;
  }
};

struct Mesh {
  std::string name;
  std::vector<Primitive> primitives;
  std::vector<GltfNum> weights;

  friend std::ostream& operator<<(std::ostream& out, Mesh& mesh) {
    out << "Mesh: " << mesh.name << std::endl;

    out << " - "
        << "primitives: " << std::endl;
    for (auto& primitive : mesh.primitives) {
      out << primitive;
    }

    if (!mesh.weights.empty()) {
      out << " - "
          << "weights: "
          << "[ ";
      for (size_t i = 0; i < mesh.weights.size(); ++i) {
        out << mesh.weights[i] << (i != mesh.weights.size() - 1 ? ", " : "");
      }
      out << " ]" << std::endl;
    }

    return out;
  }
};

struct Sparse {
  GltfInt count;
  struct {
    GltfId bufferView{INVALID_ID};
    GltfInt byteOffset{0};
    ComponentType componentType;
  } indices;
  struct {
    GltfId bufferView{INVALID_ID};
    GltfInt byteOffset{0};
  } values;
  bool used{false};

  friend std::ostream& operator<<(std::ostream& out, Sparse& sparse) {
    return out;
  }
};

struct Accessor {
  std::string name;
  GltfId bufferView{INVALID_ID};
  GltfInt byteOffset{0};
  bool normalized{false};
  ComponentType componentType{ComponentType::OTHER_TYPE};
  GltfInt count;
  AccessorType type{AccessorType::OTHER_TYPE};
  Sparse sparse;
  std::vector<GltfNum> maxValues;
  std::vector<GltfNum> minValues;

  friend std::ostream& operator<<(std::ostream& out, Accessor& accessor) {
    out << "Accessor: " << accessor.name << std::endl;

    if (accessor.bufferView != INVALID_ID) {
      out << " - "
          << "bufferView: " << accessor.bufferView << std::endl;
    }

    out << " - "
        << "byteOffset: " << accessor.byteOffset << std::endl;

    if (accessor.normalized) {
      out << " - "
          << "normalized: "
          << "FALSE" << std::endl;
    }

    out << " - "
        << "componentType: " << accessor.componentType << std ::endl;

    out << " - "
        << "count: " << accessor.count << std::endl;

    out << " - "
        << "type: " << accessor.type << std::endl;

    if (accessor.sparse.used) {
      out << " - "
          << "sparse: " << std::endl;
      out << accessor.sparse;
    }

    if (!accessor.maxValues.empty()) {
      out << " - "
          << "max: "
          << "[ ";
      for (size_t i = 0; i < accessor.maxValues.size(); ++i) {
        out << accessor.maxValues[i]
            << (i != accessor.maxValues.size() - 1 ? ", " : "");
      }
      out << " ]" << std::endl;
    }

    if (!accessor.minValues.empty()) {
      out << " - "
          << "min: "
          << "[ ";
      for (size_t i = 0; i < accessor.minValues.size(); ++i) {
        out << accessor.minValues[i]
            << (i != accessor.minValues.size() - 1 ? ", " : "");
      }
      out << " ]" << std::endl;
    }
    return out;
  }
};

struct BufferView {
  std::string name;
  GltfId buffer{INVALID_ID};
  GltfInt byteOffset{0};
  GltfInt byteLength{0};
  GltfInt byteStride{0};
  BufferViewTarget target{BufferViewTarget::OTHER_TARGET};

  friend std::ostream& operator<<(std::ostream& out, BufferView& bufferView) {
    out << "BufferView: " << bufferView.name << std::endl;

    if (bufferView.buffer != INVALID_ID) {
      out << " - "
          << "buffer: " << bufferView.buffer << std::endl;
    }

    out << " - "
        << "byteOffset: " << bufferView.byteOffset << std::endl;

    out << " - "
        << "byteLength: " << bufferView.byteLength << std::endl;

    if (bufferView.byteStride != 0) {
      out << " - "
          << "byteStride: " << bufferView.byteStride << std::endl;
    }

    out << " - "
        << "target: " << bufferView.target << std::endl;

    return out;
  }
};

struct Buffer {
  std::string name;
  std::string uri;
  GltfInt byteLength;
  std::vector<unsigned char> data;

  friend std::ostream& operator<<(std::ostream& out, Buffer& buffer) {
    out << "Buffer: " << buffer.name << std::endl;

    out << " - "
        << "uri: " << buffer.uri << std::endl;

    out << " - "
        << "byteLength: " << buffer.byteLength << std::endl;

    out << " - "
        << "data: ";
    for (auto val : buffer.data) printf("\\x%.2x", val);
    out << std::endl;

    return out;
  }
};

}  // namespace kplgltf
}  // namespace kplge