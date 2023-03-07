#pragma once

#include <memory>
#include <ostream>
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
  std::shared_ptr<SceneMesh> mesh_{};
  std::vector<SceneMeshNode> meshNodes_{};

  Matrix4X4f transform_;

 public:
  SceneMeshNode() {}
  SceneMeshNode(std::string name) : SceneBaseNode(name) {}

  std::shared_ptr<SceneMesh>& GetObject() { return mesh_; }
  std::shared_ptr<SceneMesh>& GetMesh() { return mesh_; }
  std::vector<SceneMeshNode>& GetChildren() { return meshNodes_; }
  std::vector<SceneMeshNode>& GetMeshNodes() { return meshNodes_; }

  friend std::ostream& operator<<(std::ostream& out, SceneMeshNode& node) {
    out << "Mesh Node: " << node.name_ << std::endl;
    out << *node.mesh_;
    if (!node.meshNodes_.empty()) {
      out << "> Children mesh nodes: " << std::endl;
      for (auto& child : node.meshNodes_) {
        out << child;
      }
    }
    return out;
  }
};

class SceneNode : public SceneBaseNode {
 private:
  std::vector<SceneNode> children_{};
  std::vector<SceneMeshNode> meshNodes{};

 public:
  SceneNode(std::string name) : SceneBaseNode(name) {}

  std::vector<SceneNode>& GetChildren() { return children_; }
  std::vector<SceneMeshNode>& GetMeshNodes() { return meshNodes; }

  friend std::ostream& operator<<(std::ostream& out, SceneNode& node) {
    out << "Scean node: " << node.name_ << std::endl;
    if (!node.children_.empty()) {
      out << "> Children scene nodes: " << std::endl;
      for (auto& child : node.children_) {
        out << child;
      }
    }
    if (!node.meshNodes.empty()) {
      out << "> Children mesh nodes: " << std::endl;
      for (auto& mesh : node.meshNodes) {
        out << mesh;
      }
    }
    return out;
  }
};
}  // namespace kplge