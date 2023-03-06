#pragma once

#include <memory>
#include <vector>

#include "kplcalct.h"

#include "scene-mesh.h"

using namespace kplutl;

namespace kplge {
class SceneBaseNode {
 protected:
  std::string name_{};

 public:
  SceneBaseNode() = default;
  SceneBaseNode(const SceneBaseNode& o) = default;
  SceneBaseNode(std::string name) : name_(name) {}
  virtual ~SceneBaseNode() = default;
};

class SceneMeshNode : public SceneBaseNode {
 protected:
  // std::shared_ptr<SceneMesh> mesh_{};
  std::vector<SceneMeshNode> meshNodes_{};

  Matrix4X4f transform_;

 public:
  SceneMeshNode() {}
  SceneMeshNode(std::string name) : SceneBaseNode(name) {}

  // std::shared_ptr<SceneMesh>& GetObject() { return mesh_; }
  std::vector<SceneMeshNode>& GetChildren() { return meshNodes_; }
  std::vector<SceneMeshNode>& GetMeshNodes() { return meshNodes_; }
};

class SceneNode : public SceneBaseNode {
 private:
  std::vector<SceneNode> children_{};
  std::vector<SceneMeshNode> meshNodes{};

 public:
  SceneNode(std::string name) : SceneBaseNode(name) {}

  std::vector<SceneNode>& GetChildren() { return children_; }
  std::vector<SceneMeshNode>& GetMeshNodes() { return meshNodes; }
};
}  // namespace kplge