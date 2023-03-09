#pragma once

#include <ostream>

#include "../interface/manager.h"
#include "private/matrix.h"
#include "scene-loader/gltf-constants.h"
#include "scene-node.h"
#include "scene-loader.h"

namespace kplge {
class SceneManager : public IManager {
 private:
  SceneNode root_;

 public:
  erroc Initialize() override;
  erroc Finalize() override;
  erroc Tick() override;

  SceneNode& GetSceneRenderRoot() { return root_; }

  bool LoadGltfFile(const char* path);

  friend std::ostream& operator<<(std::ostream& out, SceneManager& manager) {
    out << "Root nodes: " << std::endl;
    out << "------ " << std::endl;
    out << manager.root_ << std::endl;

    return out;
  }

 private:
  bool LoadGltfNode(
      kplgltf::GltfId nodeId, Matrix4X4f transform,
      const kplgltf::GLtfContainer& gLtfContainer);

  bool GetIndiTransformMatrix(const kplgltf::Node& node, Matrix4X4f& indi_transform);
};
}  // namespace kplge