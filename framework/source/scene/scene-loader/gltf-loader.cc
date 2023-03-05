#include "gltf-loader.h"

#include <string>
#include <map>
#include <iostream>

#include "kpllogt.h"

#include "buffer.h"
#include "gltf-constants.h"
#include "gltf-type.h"
#include "gltf-tools.h"

namespace kplge {
namespace kplgltf {

bool GltfLoader::ParseGltfFile(GLtfContainer& gLtfContainer, const char* path) {
  path_ = path;
  runtime_info("GltfLoader", "Parse gltf file '%s'\n", path);
  assetLoader.AddSearchPath("asset/glTF/");
  json gltfJson =
      json::parse(assetLoader.SyncLoadText(path).get_data_pointer());

  for (auto& el : gltfJson.items()) {
    if (el.key() == "scene") {
      if (!ParseValue(gLtfContainer.scene, gltfJson, "scene", true)) return 0;
    } else if (el.key() == "scenes") {
      if (!ParseScenes(gLtfContainer, el.value())) return 0;
    } else if (el.key() == "nodes") {
      if (!ParseNodes(gLtfContainer, el.value())) return 0;
    } else if (el.key() == "meshes") {
      if (!ParseMeshes(gLtfContainer, el.value())) return 0;
    } else if (el.key() == "accessors") {
      if (!ParseAccessors(gLtfContainer, el.value())) return 0;
    } else if (el.key() == "bufferViews") {
      if (!ParseBufferViews(gLtfContainer, el.value())) return 0;
    } else if (el.key() == "buffers") {
      if (!ParseBuffers(gLtfContainer, el.value())) return 0;
    }
  }

  return 1;
}

bool GltfLoader::ParseScenes(GLtfContainer& gLtfContainer, json& source) {
  for (auto& scene_obj : source) {
    Scene scene;

    ParseValue(scene.name, scene_obj, "name");

    ParseValueArray(scene.nodes, scene_obj, "nodes", true);

    gLtfContainer.scenes.emplace_back(std::move(scene));
  }
  return 1;
}

bool GltfLoader::ParseNodes(GLtfContainer& gLtfContainer, json& source) {
  for (auto& node_obj : source) {
    Node node;

    ParseValue(node.name, node_obj, "name");

    ParseValueArray(node.children, node_obj, "children");

    ParseValue(node.mesh, node_obj, "mesh");

    ParseValue(node.camera, node_obj, "camera");

    ParseValue(node.skin, node_obj, "skin");

    std::vector<GltfNum> matrix;
    ParseValueArray<GltfNum>(matrix, node_obj, "matrix");
    if (matrix.empty()) {
      std::vector<GltfNum> rotation;
      ParseValueArray<GltfNum>(rotation, node_obj, "rotation");
      std::vector<GltfNum> scale;
      ParseValueArray<GltfNum>(scale, node_obj, "scale");
      std::vector<GltfNum> translation;
      ParseValueArray<GltfNum>(translation, node_obj, "translation");
    } else {
      node.matrix = std::move(matrix);
    }

    ParseValueArray<GltfNum>(node.weights, node_obj, "weights");

    gLtfContainer.nodes.emplace_back(std::move(node));
  }
  return 1;
}

bool GltfLoader::ParseMeshes(GLtfContainer& gLtfContainer, json& source) {
  for (auto& mesh_obj : source) {
    Mesh mesh;

    ParseValue(mesh.name, mesh_obj, "name");

    ParsePrimitives(mesh, mesh_obj);

    ParseValueArray<GltfNum>(mesh.weights, mesh_obj, "weights");

    gLtfContainer.meshes.emplace_back(std::move(mesh));
  }
  return 1;
}

bool GltfLoader::ParsePrimitives(Mesh& mesh, json& source) {
  auto primitives_it = source.find("primitives");
  if (primitives_it != source.end()) {
    for (auto primitive_obj : primitives_it.value()) {
      Primitive primitive;

      ParseValueDict(primitive.attributes, primitive_obj, "attributes");

      ParseValue(primitive.indices, primitive_obj, "indices");

      ParseValue(primitive.material, primitive_obj, "material");

      GltfId mode{INVALID_ID};
      ParseValue(mode, primitive_obj, "mode");
      if (mode != INVALID_ID) {
        primitive.mode = static_cast<PrimitiveMode>(mode);
      }

      auto targets_it = primitive_obj.find("targets");
      if (targets_it != primitive_obj.end()) {
        for (auto target_obj : targets_it.value()) {
          std::map<std::string, GltfId> target;
          for (auto target_it = target_obj.begin();
               target_it != target_obj.end(); target_it++) {
            target[target_it.key().c_str()] = target_it.value().get<GltfId>();
          }
          primitive.targets.push_back(std::move(target));
        }
      }

      mesh.primitives.emplace_back(std::move(primitive));
    }
  }
  return 1;
}

bool GltfLoader::ParseAccessors(GLtfContainer& gLtfContainer, json& source) {
  for (auto accessors_obj : source) {
    Accessor accessor;

    ParseValue(accessor.name, accessors_obj, "name");

    ParseValue(accessor.bufferView, accessors_obj, "bufferView");

    ParseValue(accessor.byteOffset, accessors_obj, "byteOffset");

    ParseValue(accessor.normalized, accessors_obj, "normalized");

    GltfId componentType{INVALID_ID};
    if (!ParseValue(componentType, accessors_obj, "componentType", true)) {
      return 0;
    }
    accessor.componentType = static_cast<ComponentType>(componentType);

    if (!ParseValue(accessor.count, accessors_obj, "count", true)) {
      return 0;
    }

    std::string type;
    if (!ParseValue(type, accessors_obj, "type", true)) {
      return 0;
    }
    if (type.compare("SCALAR") == 0) {
      accessor.type = AccessorType::SCALAR;
    } else if (type.compare("VEC2") == 0) {
      accessor.type = AccessorType::VEC2;
    } else if (type.compare("VEC3") == 0) {
      accessor.type = AccessorType::VEC3;
    } else if (type.compare("VEC4") == 0) {
      accessor.type = AccessorType::VEC4;
    } else if (type.compare("MAT2") == 0) {
      accessor.type = AccessorType::MAT2;
    } else if (type.compare("MAT3") == 0) {
      accessor.type = AccessorType::MAT3;
    } else if (type.compare("MAT4") == 0) {
      accessor.type = AccessorType::MAT4;
    } else {
      accessor.type = AccessorType::OTHER_TYPE;
    }

    ParseValueArray<GltfNum>(accessor.maxValues, accessors_obj, "max");

    ParseValueArray<GltfNum>(accessor.minValues, accessors_obj, "min");

    gLtfContainer.accessors.emplace_back(std::move(accessor));
  }

  return 1;
}

bool GltfLoader::ParseSparse(Accessor& accessor, json& source) {
  // TODO: Parse Sparse.
  return 1;
}

bool GltfLoader::ParseBufferViews(GLtfContainer& gLtfContainer, json& source) {
  for (auto bufferView_obj : source) {
    BufferView bufferView;

    ParseValue(bufferView.name, bufferView_obj, "name");

    if (!ParseValue(bufferView.buffer, bufferView_obj, "buffer", true)) {
      return 0;
    }

    ParseValue(bufferView.byteOffset, bufferView_obj, "byteOffset");

    if (!ParseValue(
            bufferView.byteLength, bufferView_obj, "byteLength", true)) {
      return 0;
    }

    ParseValue(bufferView.byteStride, bufferView_obj, "byteStride");

    GltfId target{INVALID_ID};
    ParseValue(target, bufferView_obj, "target");
    if (target != INVALID_ID) {
      bufferView.target = static_cast<BufferViewTarget>(target);
    }

    gLtfContainer.bufferViews.emplace_back(std::move(bufferView));
  }

  return 1;
}

bool GltfLoader::ParseBuffers(GLtfContainer& gLtfContainer, json& source) {
  for (auto buffer_obj : source) {
    Buffer buffer;

    ParseValue(buffer.name, buffer_obj, "name");

    ParseValue(buffer.uri, buffer_obj, "uri");

    if (!ParseValue(buffer.byteLength, buffer_obj, "byteLength", true)) {
      return 0;
    }

    if (!ParseBufferURI(buffer)) {
      return 0;
    }

    gLtfContainer.buffers.emplace_back(std::move(buffer));
  }
  return 1;
}

bool GltfLoader::ParseBufferURI(Buffer& buffer) {
  if (buffer.uri.find("data") == 0) {
    if (!DecodeBufferURI(buffer)) return 0;
  } else {
    if (!LoadBinFile(buffer)) return 0;
  }

  return 1;
}

bool GltfLoader::DecodeBufferURI(Buffer& buffer) {
  std::string data;
  std::string header = "data:application/octet-stream;base64,";
  if (buffer.uri.find(header) == 0) {
    data = base64_decode(buffer.uri.substr(header.size()));
  }

  if (data.empty()) return 0;
  buffer.data.resize(data.size());
  std::copy(data.begin(), data.end(), buffer.data.begin());
  return 1;
}

// FIXME: Need to optimize asset loader component.
bool GltfLoader::LoadBinFile(Buffer& buffer) {
  std::string new_path = path_;
  size_t pos = new_path.find(".gltf");
  new_path.replace(pos, 5, ".bin");
  auto bin_buffer = assetLoader.SyncLoadBinary(new_path.c_str());

  if (bin_buffer.data.empty()) return 0;
  buffer.data = bin_buffer.data;
  return 1;
}

template <typename T>
bool GltfLoader::ParseValue(
    T& ret, const json& source, const char* property, bool required) {
  auto it = source.find(property);
  if (it != source.end()) {
    ret = it.value().get<T>();
    return 1;
  } else if (required) {
    return 0;
  }
  return 1;
}

template <typename T>
bool GltfLoader::ParseValueArray(
    std::vector<T>& ret, const json& source, const char* property,
    bool required) {
  auto it = source.find(property);
  ret.clear();
  if (it != source.end()) {
    for (auto id : it.value()) {
      ret.push_back(id.get<T>());
    }
    return 1;
  } else if (required) {
    return 0;
  }
  return 1;
}

template <typename T>
bool GltfLoader::ParseValueDict(
    std::map<std::string, T>& ret, const json& source, const char* property,
    bool required) {
  auto it = source.find(property);
  if (it != source.end()) {
    for (auto id = it.value().begin(); id != it.value().end(); ++id) {
      ret[id.key().c_str()] = id.value().get<T>();
    }
    return 1;
  } else if (required) {
    return 0;
  }
  return 1;
}

}  // namespace kplgltf
}  // namespace kplge