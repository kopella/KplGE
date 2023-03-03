#pragma once

#include <string>
#include <vector>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "gltf-type.h"
#include "asset-loader.h"

namespace kplge {
namespace kplgltf {
class GLtfContainer {
 public:
  Asset asset;
  GltfId scene;
  std::vector<Scene> scenes;
  std::vector<Node> nodes;
  std::vector<Mesh> meshes;
  std::vector<Accessor> accessors;
  std::vector<Buffer> buffers;
  std::vector<BufferView> bufferViews;

 public:
  friend std::ostream& operator<<(
      std::ostream& out, GLtfContainer& gLtfContainer) {
    out << gLtfContainer.asset;

    out << std::endl;
    out << "Scene: " << gLtfContainer.scene << std::endl;

    out << std::endl;
    out << "Nodes: " << std::endl;
    out << "------" << std::endl;
    for (auto& node : gLtfContainer.nodes) {
      out << node;
    }
    out << "------" << std::endl;

    out << std::endl;
    out << "Meshes: " << std::endl;
    out << "------" << std::endl;
    for (auto& mesh : gLtfContainer.meshes) {
      out << mesh;
    }
    out << "------" << std::endl;
    return out;
  }
};

class GltfLoader {
 public:
  AssetLoader assetLoader;

 public:
  GltfLoader() = default;
  ~GltfLoader() = default;

  GLtfContainer ParseGltfFile(const char* path);

 private:
  bool ParseScenes(GLtfContainer& gLtfContainer, json& source);
  bool ParseNodes(GLtfContainer& gLtfContainer, json& source);
  bool ParseMeshes(GLtfContainer& gLtfContainer, json& source);
  bool ParsePrimitives(Mesh& mesh, json& source);

  template <typename T>
  bool ParseValue(
      T& ret, const json& source, const char* property, bool required = false);

  template <typename T>
  bool ParseValueArray(
      std::vector<T>& ret, const json& source, const char* property,
      bool required = false);

  template <typename T>
  bool ParseValueDict(
      std::map<std::string, T>& ret, const json& source, const char* property,
      bool required = false);

  //   bool ParseString(
  //       std::string& ret, const json& source, const char* property,
  //       bool required = false);
  //   bool ParseStringGltfIdDict(
  //       std::map<std::string, GltfId>& ret, const json& source,
  //       const char* property, bool required = false);
  //   bool ParseGltfId(
  //       GltfId& ret, const json& source, const char* property,
  //       bool required = false);
  //   bool ParseGltfIdArray(
  //       std::vector<GltfId>& ret, const json& source, const char* property,
  //       bool required = false);
  //   bool ParseGltfInt(
  //       GltfInt& ret, const json& source, const char* property,
  //       bool required = false);
  //   bool ParseGltfIntArray(
  //       std::vector<GltfInt>& ret, const json& source, const char* property,
  //       bool required = false);
  //   bool ParseGltfNum(
  //       GltfNum& ret, const json& source, const char* property,
  //       bool required = false);
  //   bool ParseGltfNumArray(
  //       std::vector<GltfNum>& ret, const json& source, const char* property,
  //       bool required = false);
};
}  // namespace kplgltf
}  // namespace kplge