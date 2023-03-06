#include "scene-type.h"

namespace kplge {
std::ostream& operator<<(std::ostream& out, DataType& type) {
  switch (type) {
    case DataType::I8:
      out << "I8";
      break;
    case DataType::I16:
      out << "I16";
      break;
    case DataType::I32:
      out << "I32";
      break;
    case DataType::VEC2F:
      out << "VEC2F";
      break;
    case DataType::VEC3F:
      out << "VEC3F";
      break;
    case DataType::VEC4F:
      out << "VEC4F";
      break;
    case DataType::VEC2D:
      out << "VEC2D";
      break;
    case DataType::VEC3D:
      out << "VEC3D";
      break;
    case DataType::VEC4D:
      out << "VEC4D";
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

DataType GetDataTypeFromGltf(kplgltf::Accessor accessor) {
  switch (accessor.type) {
    case kplgltf::AccessorType::OTHER_TYPE:
      break;
    case kplgltf::AccessorType::SCALAR:
      switch (accessor.componentType) {
        case kplgltf::ComponentType::UNSIGNED_BYTE:
          return DataType::I8;
          break;
        case kplgltf::ComponentType::UNSIGNED_SHORT:
          return DataType::I16;
          break;
        case kplgltf::ComponentType::UNSIGNED_INT:
          return DataType::I32;
          break;
      }
      break;
    case kplgltf::AccessorType::VEC2:
      return DataType::VEC2F;
      break;
    case kplgltf::AccessorType::VEC3:
      return DataType::VEC3F;
      break;
    case kplgltf::AccessorType::VEC4:
      return DataType::VEC4F;
      break;
    case kplgltf::AccessorType::MAT2:
      break;
    case kplgltf::AccessorType::MAT3:
      break;
    case kplgltf::AccessorType::MAT4:
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