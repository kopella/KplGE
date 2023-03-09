#include "scene-manager.h"

#include <memory>
#include <utility>

#include "kpllogt.h"

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

  kplgltf::GltfId scene_id =
      gLtfContainer.scene != kplgltf::INVALID_ID ? gLtfContainer.scene : 0;

  auto& scene = gLtfContainer.scenes[scene_id];
  root_.name_ = scene.name;

  for (auto id : scene.nodes) {
    Matrix4X4f transform;
    identity(transform);
    LoadGltfNode(id, transform, gLtfContainer);
  }

  return 1;
}

bool SceneManager::LoadGltfNode(
    kplgltf::GltfId nodeId, Matrix4X4f transform,
    const kplgltf::GLtfContainer& gLtfContainer) {
  auto node = gLtfContainer.nodes[nodeId];

  // Load mesh.
  if (node.mesh != kplgltf::INVALID_ID) {
    SceneMeshNode meshNode{node.name};

    Matrix4X4f indi_transform;
    identity(indi_transform);

    GetIndiTransformMatrix(node, indi_transform);

    meshNode.GetTransforms().emplace_back(
        std::move(multiply(transform, indi_transform)));

    meshNode.GetObject() = std::make_shared<SceneMesh>(
        gLtfContainer.meshes[node.mesh], gLtfContainer);

    root_.GetMeshNodes().emplace_back(std::move(meshNode));
  }

  // Process child node.
  if (!node.children.empty()) {
    for (auto id : node.children) {
      Matrix4X4f indi_transform;
      identity(indi_transform);

      GetIndiTransformMatrix(node, indi_transform);

      LoadGltfNode(id, multiply(transform, indi_transform), gLtfContainer);
    }
  }
  return 1;
}

bool SceneManager::GetIndiTransformMatrix(
    const kplgltf::Node& node, Matrix4X4f& indi_transform) {
  if (!node.matrix.empty()) {
    indi_transform =
        transpose(Matrix4X4f{node.matrix.begin(), node.matrix.end()});

  } else {
    if (!node.scale.empty())
      indi_transform = multiply(
          build_scale_matrix(node.scale[0], node.scale[1], node.scale[2]),
          indi_transform);
    if (!node.rotation.empty())
      indi_transform = multiply(
          build_rotation_matrix(
              node.rotation[0], node.rotation[1], node.rotation[2],
              node.rotation[3]),
          indi_transform);
    if (!node.translation.empty())
      indi_transform = multiply(
          build_translation_matrix(
              node.translation[0], node.translation[1], node.translation[2]),
          indi_transform);
  }

  return 1;
}

}  // namespace kplge