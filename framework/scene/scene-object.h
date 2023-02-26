#pragma once
#include <iostream>

#include "constants.h"
#include "kpl-guid.h"

namespace kplge {
enum SceneObjectType {
  TYPE_VERTEX = 0,
  TYPE_INDEX,
  TYPE_MESH,
  TYPE_MATERIAL,
};

std::ostream& operator<<(std::ostream& out, const SceneObjectType type);

class SceneObject {
 public:
  SceneObject() = delete;
  SceneObject(SceneObject& obj) = delete;
  SceneObject& operator=(SceneObject& obj) = delete;

 protected:
  Guid guid_;
  SceneObjectType type_;

 protected:
  explicit SceneObject(SceneObjectType type) : type_(type) {
    guid_ = generate_guid();
  };
  SceneObject(SceneObject&& obj) : guid_(obj.guid_), type_(obj.type_){};
  SceneObject& operator=(SceneObject&& obj) {
    this->guid_ = obj.guid_;
    this->type_ = obj.type_;
    return *this;
  };
  virtual ~SceneObject() = default;

 public:
  friend std::ostream& operator<<(std::ostream& out, const SceneObject& obj) {
    out << std::endl;
    out << "Scene Object: " << obj.type_ << std::endl
        << "- Guid: " << obj.guid_ << std::endl;
    return out;
  }
};
}  // namespace kplge
