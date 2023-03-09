#pragma once

#include <string>
#include <vector>

#include "gltf-constants.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "gltf-type.h"
#include "asset-loader.h"

namespace kplge {
namespace kplgltf {
class GLtfContainer {
 public:
  Asset asset;
  GltfId scene{INVALID_ID};
  std::vector<Scene> scenes;
  std::vector<Node> nodes;
  std::vector<Mesh> meshes;
  std::vector<Accessor> accessors;
  std::vector<BufferView> bufferViews;
  std::vector<Buffer> buffers;

 public:
  friend std::ostream& operator<<(
      std::ostream& out, GLtfContainer& gLtfContainer) {
    out << gLtfContainer.asset;

    out << std::endl;
    out << "Scene: " << gLtfContainer.scene << std::endl;

    out << std::endl;
    out << "Scenes: " << std::endl;
    out << " - "
        << "count: " << gLtfContainer.scenes.size() << std::endl;
    out << "------" << std::endl;
    for (auto& scene : gLtfContainer.scenes) {
      out << scene;
    }
    out << "------" << std::endl;

    out << std::endl;
    out << "Nodes: " << std::endl;
    out << " - "
        << "count: " << gLtfContainer.nodes.size() << std::endl;
    out << "------" << std::endl;
    for (auto& node : gLtfContainer.nodes) {
      out << node;
    }
    out << "------" << std::endl;

    out << std::endl;
    out << "Meshes: " << std::endl;
    out << " - "
        << "count: " << gLtfContainer.meshes.size() << std::endl;
    out << "------" << std::endl;
    for (auto& mesh : gLtfContainer.meshes) {
      out << mesh;
    }
    out << "------" << std::endl;

    out << std::endl;
    out << "Accessors: " << std::endl;
    out << " - "
        << "count: " << gLtfContainer.accessors.size() << std::endl;
    out << "------" << std::endl;
    for (auto& accessor : gLtfContainer.accessors) {
      out << accessor;
    }
    out << "------" << std::endl;

    out << std::endl;
    out << "BufferViews: " << std::endl;
    out << " - "
        << "count: " << gLtfContainer.bufferViews.size() << std::endl;
    out << "------" << std::endl;
    for (auto& bufferView : gLtfContainer.bufferViews) {
      out << bufferView;
    }
    out << "------" << std::endl;

    out << std::endl;
    out << "Buffer: " << std::endl;
    out << " - "
        << "count: " << gLtfContainer.buffers.size() << std::endl;
    out << "------" << std::endl;
    for (auto& buffer : gLtfContainer.buffers) {
      out << buffer;
    }
    out << "------" << std::endl;

    return out;
  }
};

class GltfLoader {
 public:
  AssetLoader assetLoader;

 private:
  std::string path_;

 public:
  GltfLoader() = default;
  ~GltfLoader() = default;

  bool ParseGltfFile(GLtfContainer& gLtfContainer, const char* path);

 private:
  bool ParseScenes(GLtfContainer& gLtfContainer, json& source);
  bool ParseNodes(GLtfContainer& gLtfContainer, json& source);
  bool ParseMeshes(GLtfContainer& gLtfContainer, json& source);
  bool ParsePrimitives(Mesh& mesh, json& source);
  bool ParseAccessors(GLtfContainer& gLtfContainer, json& source);
  bool ParseSparse(Accessor& accessor, json& source);
  bool ParseBufferViews(GLtfContainer& gLtfContainer, json& source);
  bool ParseBuffers(GLtfContainer& gLtfContainer, json& source);
  bool ParseBufferURI(Buffer& buffer);

  bool DecodeBufferURI(Buffer& buffer);
  bool LoadBinFile(Buffer& buffer);

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
};

}  // namespace kplgltf
}  // namespace kplge