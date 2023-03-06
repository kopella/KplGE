#include "scene-manager.h"

#include <memory>
#include <vector>

#include "kpllogt.h"

#include "private/info.h"
#include "scene-loader.h"
#include "scene-mesh.h"
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

  auto scene_node = std::move(std::make_shared<SceneNode>(scene.name));

  LoadGltfNode(scene_node, scene.nodes, gLtfContainer);

  // roots_.emplace_back(scene_node);
  return 1;
}

bool SceneManager::LoadGltfNode(
    std::shared_ptr<SceneNode>& parent, std::vector<kplgltf::GltfId>& node_ids,
    kplgltf::GLtfContainer& gLtfContainer) {
  for (auto& node_id : node_ids) {
    auto& node = gLtfContainer.nodes[node_id];

    // Only children:
    if (node.mesh == kplgltf::INVALID_ID &&
        node.camera == kplgltf::INVALID_ID &&
        node.skin == kplgltf::INVALID_ID) {
      std::shared_ptr<SceneNode> new_node =
          std::make_shared<SceneNode>(node.name);
      if (!node.children.empty()) {
        LoadGltfNode(new_node, node.children, gLtfContainer);
      }
      parent->GetNodes().emplace_back(std::move(new_node));
    }

    // Mesh:
    if (node.mesh != kplgltf::INVALID_ID) {
      auto mesh_node = std::make_shared<SceneMeshNode>(node.name);

      mesh_node->GetObject() = std::move(std::make_shared<SceneMesh>(
          gLtfContainer.meshes[node.mesh], gLtfContainer));

      std::shared_ptr<SceneMeshNode> new_node = std::move(mesh_node);
      if (!node.children.empty()) {
        LoadGltfMesh(new_node, node.children, gLtfContainer);
      }
      parent->GetNodes().emplace_back(std::move(mesh_node));
    }
    // Camera:

    // Skin:
  }

  return 1;
}

bool SceneManager::LoadGltfMesh(
    std::shared_ptr<SceneMeshNode>& parent,
    std::vector<kplgltf::GltfId>& node_ids,
    kplgltf::GLtfContainer& gLtfContainer) {
  for (auto& node_id : node_ids) {
    auto& node = gLtfContainer.nodes[node_id];
    auto mesh_node = std::make_shared<SceneMeshNode>(node.name);

    mesh_node->GetObject() = std::move(std::make_shared<SceneMesh>(
        gLtfContainer.meshes[node.mesh], gLtfContainer));

    std::shared_ptr<SceneMeshNode> new_node = std::move(mesh_node);
    if (!node.children.empty()) {
      LoadGltfMesh(new_node, node.children, gLtfContainer);
    }
    parent->GetNodes().emplace_back(std::move(mesh_node));
  }
  return 1;
}
}  // namespace kplge