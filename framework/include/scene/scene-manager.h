#pragma once

#include <vcruntime.h>
#include <ostream>

#include "../interface/manager.h"
#include "scene-node.h"
#include "scene-loader.h"

namespace kplge {
class SceneManager : IManager {
 private:
  std::vector<SceneNode> roots_;

 public:
  erroc Initialize() override;
  erroc Finalize() override;
  erroc Tick() override;

  SceneNode& GetSceneRoot(size_t n) { return roots_.at(n); }

  bool LoadGltfFile(const char* path);

 private:
  void dump(std::ostream& out) {
    out << "Root nodes: " << std::endl;
    out << "------ " << std::endl;
    for (size_t i = 0; i < roots_.size(); ++i) {
      out << "Root " << i << " : " << std::endl;
    }
  }

  bool LoadGltfNode(
      SceneNode& parent, std::vector<kplgltf::GltfId>& nodeIds,
      kplgltf::GLtfContainer& gLtfContainer);

  bool LoadGltfMeshNode(
      SceneMeshNode& parent, std::vector<kplgltf::GltfId>& nodeIds,
      kplgltf::GLtfContainer& gLtfContainer);
};
}  // namespace kplge