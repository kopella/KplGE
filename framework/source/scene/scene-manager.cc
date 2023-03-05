#include "scene-manager.h"

#include "kpllogt.h"

#include "scene-loader.h"
#include "scene-node.h"

namespace kplge {
erroc SceneManager::Initialize() { return KPL_NO_ERR; }
erroc SceneManager::Finalize() { return KPL_NO_ERR; }
erroc SceneManager::Tick() { return KPL_NO_ERR; }

bool SceneManager::LoadGltfFile(const char* path) {
  runtime_info("SceneManager", "Load gltf file: '%s'\n", path);

  kplgltf::GltfLoader gltfLoader;
  kplgltf::GLtfContainer gLtfContainer;

  gltfLoader.ParseGltfFile(gLtfContainer, path);

  auto& scene = gLtfContainer.scenes[gLtfContainer.scene];

  SceneNode root(scene.name);

  LoadGltfNode(root, scene.nodes, gLtfContainer);

  roots_.emplace_back(std::move(root));
  return 1;
}

bool SceneManager::LoadGltfNode(
    SceneNode& parent, std::vector<kplgltf::GltfId>& nodeIds,
    kplgltf::GLtfContainer& gLtfContainer) {
  for (auto& nodeId : nodeIds) {
    auto& node = gLtfContainer.nodes[nodeId];

    // Only children:
    if (node.mesh == kplgltf::INVALID_ID &&
        node.camera == kplgltf::INVALID_ID &&
        node.skin == kplgltf::INVALID_ID) {
      SceneNode newNode = SceneNode(node.name);
      std::cout << "sign: " << std::endl;
      if (!node.children.empty()) {
        LoadGltfNode(newNode, node.children, gLtfContainer);
      }

      parent.GetChildren().emplace_back(std::move(newNode));
    }

    // Mesh:
    if (node.mesh != kplgltf::INVALID_ID) {
      SceneMeshNode meshNode = SceneMeshNode(node.name);
      std::cout << "test: mesh" << std::endl;
      if (!node.children.empty()) {
        // LoadGltfNode(meshNode, node.children, gLtfContainer);
      }

      parent.GetMeshNodes().emplace_back(std::move(meshNode));
    }
  }

  return 1;
}
}  // namespace kplge