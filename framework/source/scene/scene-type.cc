#include "scene-type.h"

namespace kplge {
std::ostream& operator<<(std::ostream& out, VertexDataType& type) {
  switch (type) {
    case VertexDataType::VEC2F:
      out << "VEC2F";
      break;
    case VertexDataType::VEC3F:
      out << "VEC3F";
      break;
    case VertexDataType::VEC4F:
      out << "VEC4F";
      break;
    case VertexDataType::VEC2D:
      out << "VEC2D";
      break;
    case VertexDataType::VEC3D:
      out << "VEC3D";
      break;
    case VertexDataType::VEC4D:
      out << "VEC4D";
      break;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, IndexDataType& type) {
  switch (type) {
    case IndexDataType::I8:
      out << "I8";
      break;
    case IndexDataType::I16:
      out << "I16";
      break;
    case IndexDataType::I32:
      out << "I32";
      break;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, VertexAttribute& attribute) {
  switch (attribute) {
    case VertexAttribute::POSITION:
      out << "POSITION";
      break;
    case VertexAttribute::NORMAL:
      out << "NORMAL";
      break;
    case VertexAttribute::TEXCOORD:
      out << "TEXCOORD";
      break;
    case VertexAttribute::TANGENT:
      out << "TANGENT";
      break;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, PrimitiveMode& mode) {
  switch (mode) {
    case PrimitiveMode::POINTS:
      out << "POINTS";
      break;
    case PrimitiveMode::LINES:
      out << "LINES";
      break;
    case PrimitiveMode::LINE_LOOP:
      out << "LINE_LOOP";
      break;
    case PrimitiveMode::LINE_STRIP:
      out << "LINE_STRIP";
      break;
    case PrimitiveMode::TRIANGLES:
      out << "TRIANGLES";
      break;
    case PrimitiveMode::TRIANGLE_STRIP:
      out << "TRIANGLE_STRIP";
      break;
    case PrimitiveMode::TRIANGLE_FAN:
      out << "TRIANGLE_FAN";
      break;
  }
  return out;
}

IndexDataType GetIndexDataTypeFromGltf(kplgltf::Accessor accessor) {
  switch (accessor.type) {
    case kplgltf::AccessorType::SCALAR:
      switch (accessor.componentType) {
        case kplgltf::ComponentType::UNSIGNED_BYTE:
          return IndexDataType::I8;
          break;
        case kplgltf::ComponentType::UNSIGNED_SHORT:
          return IndexDataType::I16;
          break;
        case kplgltf::ComponentType::UNSIGNED_INT:
          return IndexDataType::I32;
          break;
      }
      break;
  }
}

VertexDataType GetVertexDataTypeFromGltf(kplgltf::Accessor accessor) {
  switch (accessor.type) {
    case kplgltf::AccessorType::VEC2:
      return VertexDataType::VEC2F;
      break;
    case kplgltf::AccessorType::VEC3:
      return VertexDataType::VEC3F;
      break;
    case kplgltf::AccessorType::VEC4:
      return VertexDataType::VEC4F;
      break;
  }
}

PrimitiveMode GetPrimitiveModeFromGltf(kplgltf::PrimitiveMode type) {
  switch (type) {
    case kplgltf::PrimitiveMode::POINTS:
      return PrimitiveMode::POINTS;
      break;
    case kplgltf::PrimitiveMode::LINES:
      return PrimitiveMode::LINES;
      break;
    case kplgltf::PrimitiveMode::LINE_LOOP:
      return PrimitiveMode::LINE_LOOP;
      break;
    case kplgltf::PrimitiveMode::LINE_STRIP:
      return PrimitiveMode::LINE_STRIP;
      break;
    case kplgltf::PrimitiveMode::TRIANGLES:
      return PrimitiveMode::TRIANGLES;
      break;
    case kplgltf::PrimitiveMode::TRIANGLE_STRIP:
      return PrimitiveMode::TRIANGLE_STRIP;
      break;
    case kplgltf::PrimitiveMode::TRIANGLE_FAN:
      return PrimitiveMode::TRIANGLE_FAN;
      break;
  }
}

}  // namespace kplge