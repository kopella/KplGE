#include <iostream>

#include "scene-type.h"
#include "scene-object.h"

namespace kplge {
std::ostream& operator<<(std::ostream& out, const SceneObjectType type) {
  switch (type) {
    case SceneObjectType::TYPE_VERTEX:
      out << TYPE_NAME_VERTEX;
      break;
    case SceneObjectType::TYPE_INDEX:
      out << TYPE_NAME_INDEX;
      break;
    case SceneObjectType::TYPE_MESH:
      out << TYPE_NAME_MESH;
      break;
    case SceneObjectType::TYPE_MATERIAL:
      out << TYPE_NAME_MATERIAL;
      break;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, const SceneObject& obj) {
  out << std::endl;
  out << "Scene Object: " << obj.type_ << std::endl
      << "- Guid: " << obj.guid_ << std::endl;
  return out;
}
}  // namespace kplge