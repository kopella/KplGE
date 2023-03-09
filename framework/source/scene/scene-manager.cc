#include "scene-manager.h"

#include <memory>
#include <utility>

#include "kpllogt.h"

#include "private/matrix.h"
#include "private/tools.h"
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
      if (!node.matrix.empty()) {
        newNode.GetTransforms().emplace_back(
            transpose(Matrix4X4f{node.matrix.begin(), node.matrix.end()}));
      } else {
        Matrix4X4f res;
        identity(res);
        if (!node.scale.empty())
          res = multiply(
              build_scale_matrix(node.scale[0], node.scale[1], node.scale[2]),
              res);
        if (!node.rotation.empty())
          res = multiply(
              build_rotation_matrix(
                  node.rotation[0], node.rotation[1], node.rotation[2],
                  node.rotation[3]),
              res);
        if (!node.translation.empty())
          res = multiply(
              build_translation_matrix(
                  node.translation[0], node.translation[1],
                  node.translation[2]),
              res);
        newNode.GetTransforms().emplace_back(std::move(res));
      }
      if (!node.children.empty()) {
        LoadGltfNode(newNode, node.children, gLtfContainer);
      }
      parent.GetChildren().emplace_back(std::move(newNode));
    }

    // Mesh:
    if (node.mesh != kplgltf::INVALID_ID) {
      SceneMeshNode meshNode = SceneMeshNode(node.name);
      if (!node.matrix.empty()) {
        meshNode.GetTransforms().emplace_back(
            transpose(Matrix4X4f{node.matrix.begin(), node.matrix.end()}));
      } else {
        Matrix4X4f res;
        identity(res);
        if (!node.scale.empty())
          res = multiply(
              build_scale_matrix(node.scale[0], node.scale[1], node.scale[2]),
              res);
        if (!node.rotation.empty())
          res = multiply(
              build_rotation_matrix(
                  node.rotation[0], node.rotation[1], node.rotation[2],
                  node.rotation[3]),
              res);
        if (!node.translation.empty())
          res = multiply(
              build_translation_matrix(
                  node.translation[0], node.translation[1],
                  node.translation[2]),
              res);
        meshNode.GetTransforms().emplace_back(std::move(res));
      }
      meshNode.GetObject() = std::make_shared<SceneMesh>(
          gLtfContainer.meshes[node.mesh], gLtfContainer);
      if (!node.children.empty()) {
        LoadGltfMeshNode(meshNode, node.children, gLtfContainer);
      }
      parent.GetMeshNodes().emplace_back(std::move(meshNode));
    }
  }

  return 1;
}

bool SceneManager::LoadGltfMeshNode(
    SceneMeshNode& parent, std::vector<kplgltf::GltfId>& nodeIds,
    kplgltf::GLtfContainer& gLtfContainer) {
  for (auto& nodeId : nodeIds) {
    auto& node = gLtfContainer.nodes[nodeId];
    SceneMeshNode meshNode = SceneMeshNode(node.name);
    if (!node.children.empty()) {
      LoadGltfMeshNode(meshNode, node.children, gLtfContainer);
    }
    parent.GetMeshNodes().emplace_back(std::move(meshNode));
  }

  return 1;
}
}  // namespace kplge