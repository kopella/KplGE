#pragma once

#include <memory>
#include <ostream>
#include <vector>

#include "kplcalct.h"

#include "private/matrix.h"
#include "private/vector.h"
#include "scene-mesh.h"

using namespace kplutl;

namespace kplge {
class SceneBaseNode {
 public:
  std::string name_{};

  std::vector<Matrix4X4f> transforms_;

 public:
  SceneBaseNode() = default;
  SceneBaseNode(const SceneBaseNode& o) = default;
  SceneBaseNode(std::string name) : name_(name) {}
  virtual ~SceneBaseNode() = default;

  std::vector<Matrix4X4f>& GetTransforms() { return transforms_; }

  Matrix4X4f GetTransformMatrix() {
    Matrix4X4f res;
    identity(res);
    for (auto transform : transforms_) {
      res = multiply(transform, res);
    }
    return res;
  }
};

class SceneMeshNode : public SceneBaseNode {
 protected:
  std::shared_ptr<SceneMesh> mesh_{};
  std::vector<SceneMeshNode> meshNodes_{};

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
  std::vector<SceneNode> children_{};
  std::vector<SceneMeshNode> meshNodes{};
  std::vector<SceneCameraNode> meshCameraNodes{};

 public:
  SceneNode(std::string name) : SceneBaseNode(name) {}

  std::vector<SceneNode>& GetChildren() { return children_; }
  std::vector<SceneMeshNode>& GetMeshNodes() { return meshNodes; }
  std::vector<SceneCameraNode>& GetCameraNodes() { return meshCameraNodes; }

  friend std::ostream& operator<<(std::ostream& out, SceneNode& node) {
    out << "Scean node: " << node.name_ << std::endl;
    if (!node.transforms_.empty()) {
      out << " - Transform matrix: " << node.GetTransformMatrix();
    }
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