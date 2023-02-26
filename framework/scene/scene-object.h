#pragma once
#include <iostream>

#include "constants.h"
#include "kpl-guid.h"
#include "scene-type.h"

namespace kplge {
  
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
  friend std::ostream& operator<<(std::ostream& out, const SceneObject& obj);
};
}  // namespace kplge
