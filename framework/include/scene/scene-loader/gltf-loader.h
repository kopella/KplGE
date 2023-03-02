#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <map>

#include "gltf-constants.h"
#include "kplcalct.h"

using namespace kplutl;

namespace kplgltf {
using glTFid = unsigned int;
using glTFnum = float;
using glTFint = int;

const glTFid INVALID_ID = -1;

struct Asset {
  std::string version{"2.0"};
  std::string copyright;
  std::string generator;
};

struct Scene {
  std::string name;
  std::vector<glTFid> nodes;
};

struct Node {
  std::string name;
  std::vector<glTFid> children;
  glTFid mesh;
  glTFid skin;
  Vector4f rotation{0.0, 0.0, 0.0, 1.0};
  Vector3f scale{1.0, 1.0, 1.0};
  Vector3f translation{0.0, 0.0, 0.0};
  Matrix4X4f matrix{
      {1.0, 0.0, 0.0, 0.0},
      {0.0, 1.0, 0.0, 0.0},
      {0.0, 0.0, 1.0, 0.0},
      {0.0, 0.0, 0.0, 1.0}};
  std::vector<glTFnum> weights;
};

struct Primitive {
  std::map<std::string, int> attributes;
  glTFid indices{INVALID_ID};
  glTFid material{INVALID_ID};
  PrimitiveMode mode{4};
  std::vector<std::map<std::string, int>> targets;
};

struct Mesh {
  std::string name;
  std::vector<Primitive> primitives;
  std::vector<std::map<std::string, int>> weights;
};

struct Buffer {
  std::string name;
  std::string uri;
  std::vector<unsigned char> data;
};

struct BufferView {
  std::string name;
  glTFid buffer{INVALID_ID};
  glTFint byteOffset{0};
  glTFint byteLength{0};
  glTFint byteStride{0};
  BufferViewTarget target{BufferViewTarget::OTHER_TARGET};
};

struct Accessor {
  std::string name;
  glTFid bufferView{INVALID_ID};
  glTFint byteOffset{0};
  ComponentType componentType{ComponentType::OTHER_TYPE};
  bool normalized;
  glTFint count;
  AccessorType accessorType{AccessorType::OTHER_TYPE};
};

}  // namespace kplgltf