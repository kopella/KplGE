#pragma once

#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "gltf-constants.h"

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

struct Asset {
  std::string version{"2.0"};
  std::string copyright;
  std::string generator;

  friend std::ostream& operator<<(std::ostream& out, Asset& asset) {
    out << "Version: " << asset.version << std::endl;
    if (!asset.generator.empty())
      out << "Generator: " << asset.generator << std::endl;
    if (!asset.copyright.empty())
      out << "Copyright: " << asset.copyright << std::endl;
    return out;
  }
};

struct Scene {
  std::string name;
  std::vector<GltfId> nodes;

  friend std::ostream& operator<<(std::ostream& out, Scene& scene) {
    out << "Scene: " << scene.name << std::endl;
    out << "Nodes: "
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
  GltfId skin{INVALID_ID};
  Matrix4X4Num matrix{DEAFULA_MATRIX};
  Vector4Num rotation{DEFAULT_ROTATION};
  Vector3Num scale{DEFAULT_SCALE};
  Vector3Num translation{DEFAULT_TRANSLATION};
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
          << "Mesh: " << node.mesh << std::endl;
    }

    if (node.skin != INVALID_ID) {
      out << " - "
          << "Skin: " << node.skin << std::endl;
    }

    if (node.matrix != DEAFULA_MATRIX) {
      out << " - "
          << "Matrix: " << std::endl;
      for (size_t i = 0; i < 4; ++i) {
        out << "   "
            << "[ ";
        for (size_t j = 0; j < 4; ++j) {
          out << node.matrix[i * 4 + j] << (j != 3 ? ", " : "");
        }
        out << " ]" << std::endl;
      }
    } else {
      if (node.rotation != DEFAULT_ROTATION) {
        out << " - "
            << "Rotation: "
            << "[ ";
        for (size_t i = 0; i < 4; ++i) {
          out << node.rotation[i] << (i != 3 ? ", " : "");
        }
        out << " ]" << std::endl;
      }

      if (node.scale != DEFAULT_SCALE) {
        out << " - "
            << "Scale: "
            << "[ ";
        for (size_t i = 0; i < 3; ++i) {
          out << node.scale[i] << (i != 2 ? ", " : "");
        }
        out << " ]" << std::endl;
      }

      if (node.translation != DEFAULT_TRANSLATION) {
        out << " - "
            << "Translation: "
            << "[ ";
        for (size_t i = 0; i < 3; ++i) {
          out << node.translation[i] << (i != 2 ? ", " : "");
        }
        out << " ]" << std::endl;
      }
    }

    if (!node.weights.empty()) {
      out << " - "
          << "Weights: "
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
  PrimitiveMode mode{4};
  std::vector<std::map<std::string, GltfId>> targets;

  friend std::ostream& operator<<(std::ostream& out, Primitive& primitive) {
    out << " - "
        << "Attributes: " << std::endl;
    for (auto& [key, value] : primitive.attributes) {
      out << " - "
          << " - " << key << value << std::endl;
    }

    out << " - "
        << "Indices: ";
    if (primitive.indices != INVALID_ID)
      out << primitive.indices << std::endl;
    else
      out << "INVALID" << std::endl;

    out << " - "
        << "Material: ";
    if (primitive.material != INVALID_ID)
      out << primitive.material << std::endl;
    else
      out << "INVALID" << std::endl;

    out << " - "
        << "Mode: ";
    switch (primitive.mode) {
      case PrimitiveMode::POINTS:
        out << "POINTS" << std::endl;
        break;
      case PrimitiveMode::LINES:
        out << "LINES" << std::endl;
        break;
      case PrimitiveMode::LINE_LOOP:
        out << "LINE_LOOP" << std::endl;
        break;
      case PrimitiveMode::LINE_STRIP:
        out << "LINE_STRIP" << std::endl;
        break;
      case PrimitiveMode::TRIANGLES:
        out << "TRIANGLES" << std::endl;
        break;
      case PrimitiveMode::TRIANGLE_STRIP:
        out << "TRIANGLE_STRIP" << std::endl;
        break;
      case PrimitiveMode::TRIANGLE_FAN:
        out << "TRIANGLE_FAN" << std::endl;
        break;
    }

    out << " - "
        << "Targets: ";
    if (!primitive.targets.empty()) {
      out << std::endl;
      for (auto& target : primitive.targets) {
        for (auto& [key, value] : target) {
          out << " - "
              << " - " << key << value << std::endl;
        }
        out << std::endl;
      }
    } else {
      out << "NULL" << std::endl;
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
        << "Primitives: " << std::endl;
    for (auto& primitive : mesh.primitives) {
      out << " -  - " << std::endl;
      out << primitive;
    }

    if (!mesh.weights.empty()) {
      out << " - "
          << "Weights: "
          << "[ ";
      for (size_t i = 0; i < mesh.weights.size(); ++i) {
        out << mesh.weights[i] << (i != mesh.weights.size() - 1 ? ", " : "");
      }
      out << " ]" << std::endl;
    }

    return out;
  }
};

struct Accessor {
  std::string name;
  GltfId bufferView{INVALID_ID};
  GltfInt byteOffset{0};
  ComponentType componentType{ComponentType::OTHER_TYPE};
  GltfInt count;
  bool normalized{false};
  AccessorType accessorType{AccessorType::OTHER_TYPE};
};

struct Buffer {
  std::string name;
  std::string uri;
  GltfInt byteLength;
  unsigned char* data;
};

struct BufferView {
  std::string name;
  GltfId buffer{INVALID_ID};
  GltfInt byteOffset;
  GltfInt byteLength;
  GltfInt byteStride;
  BufferViewTarget target{BufferViewTarget::OTHER_TARGET};
};

}  // namespace kplgltf
}  // namespace kplge