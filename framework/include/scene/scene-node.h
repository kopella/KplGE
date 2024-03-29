#pragma once

#include <memory>
#include <ostream>
#include <vector>

#include "kplcalct.h"

#include "scene-mesh.h"

using namespace kplutl;

namespace kplge {
class SceneBaseNode {
 public:
  std::string name_;

 public:
  SceneBaseNode() = default;
  SceneBaseNode(const SceneBaseNode& o) = default;
  SceneBaseNode(std::string name) : name_(name) {}
  virtual ~SceneBaseNode() = default;
};

class SceneMeshNode : public SceneBaseNode {
 protected:
  std::shared_ptr<SceneMesh> mesh_;
  std::vector<SceneMeshNode> meshNodes_;

  std::vector<Matrix4X4f> transforms_;

 public:
  SceneMeshNode() {}
  SceneMeshNode(std::string name) : SceneBaseNode(name) {}

  std::shared_ptr<SceneMesh>& GetObject() { return mesh_; }
  std::shared_ptr<SceneMesh>& GetMesh() { return mesh_; }
  std::vector<SceneMeshNode>& GetChildren() { return meshNodes_; }
  std::vector<SceneMeshNode>& GetMeshNodes() { return meshNodes_; }

  std::vector<Matrix4X4f>& GetTransforms() { return transforms_; }
  Matrix4X4f GetTransformMatrix() {
    Matrix4X4f res;
    identity(res);
    for (auto transform : transforms_) {
      res = multiply(transform, res);
    }
    return res;
  }

  PrimitiveMode GetPrimitiveMode() { return mesh_->GetPrimitiveMode(); }

  friend std::ostream& operator<<(std::ostream& out, SceneMeshNode& node) {
    out << "Mesh Node: " << node.name_ << std::endl;
    out << *node.mesh_;
    if (!node.transforms_.empty()) {
      out << " - Transform matrix: " << node.GetTransformMatrix();
    }
    if (!node.meshNodes_.empty()) {
      out << "> Children mesh nodes: " << std::endl;
      for (auto& child : node.meshNodes_) {
        out << child;
      }
    }
    return out;
  }
};

class SceneCameraNode : public SceneBaseNode {};

class SceneNode : public SceneBaseNode {
 private:
  std::vector<SceneMeshNode> meshNodes;
  std::vector<SceneCameraNode> meshCameraNodes;

 public:
  SceneNode() = default;
  SceneNode(std::string name) : SceneBaseNode(name) {}

  std::vector<SceneMeshNode>& GetMeshNodes() { return meshNodes; }
  std::vector<SceneCameraNode>& GetCameraNodes() { return meshCameraNodes; }

  friend std::ostream& operator<<(std::ostream& out, SceneNode& node) {
    out << "Scean node: " << node.name_ << std::endl;
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