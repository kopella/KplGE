#include <iostream>

#include "scene-object.h"

namespace kplge {
std::ostream& operator<<(std::ostream& out, const SceneObjectType type) {
  switch (type) {
    case TYPE_VERTEX:
      out << TYPE_NAME_VERTEX;
      break;
    case TYPE_INDEX:
      out << TYPE_NAME_INDEX;
      break;
    case TYPE_MESH:
      out << TYPE_NAME_MESH;
      break;
    case TYPE_MATERIAL:
      out << TYPE_NAME_MATERIAL;
      break;
  }
  return out;
}

}  // namespace kplge