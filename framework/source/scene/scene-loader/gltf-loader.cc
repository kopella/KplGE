#include "gltf-loader.h"

#include <string>
#include <map>
#include <iostream>

#include "gltf-constants.h"
#include "gltf-type.h"

namespace kplge {
namespace kplgltf {

GLtfContainer GltfLoader::ParseGltfFile(const char* path) {
  assetLoader.AddSearchPath("asset/glTF/");
  json gltfJson = json::parse(assetLoader.SyncLoadText(path).get_data());

  GLtfContainer gLtfContainer;
  for (auto& el : gltfJson.items()) {
    if (el.key() == "scene") {
      gLtfContainer.scene = el.value().get<GltfId>();
    } else if (el.key() == "scenes") {
      ParseScenes(gLtfContainer, el.value());
    } else if (el.key() == "nodes") {
      ParseNodes(gLtfContainer, el.value());
    } else if (el.key() == "meshes") {
      ParseMeshes(gLtfContainer, el.value());
    }
  }

  return gLtfContainer;
}

bool GltfLoader::ParseScenes(GLtfContainer& gLtfContainer, json& source) {
  for (auto& scene_obj : source) {
    Scene scene;

    ParseValue<std::string>(scene.name, scene_obj, "name");

    ParseValueArray<GltfId>(scene.nodes, scene_obj, "nodes", true);

    gLtfContainer.scenes.emplace_back(std::move(scene));
  }
  return 1;
}

bool GltfLoader::ParseNodes(GLtfContainer& gLtfContainer, json& source) {
  for (auto& node_obj : source) {
    Node node;

    ParseValue<std::string>(node.name, node_obj, "name");

    ParseValueArray<GltfId>(node.children, node_obj, "children");

    ParseValue<GltfId>(node.mesh, node_obj, "mesh");

    ParseValue<GltfId>(node.skin, node_obj, "skin");

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

    ParseValue<std::string>(mesh.name, mesh_obj, "name");

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

      ParseValueDict<GltfId>(primitive.attributes, primitive_obj, "attributes");

      ParseValue<GltfId>(primitive.indices, primitive_obj, "indices");

      ParseValue<GltfId>(primitive.material, primitive_obj, "material");

      GltfId mode{INVALID_ID};
      ParseValue<GltfId>(mode, primitive_obj, "mode");
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

template <typename T>
bool GltfLoader::ParseValue(
    T& ret, const json& source, const char* property, bool required) {
  auto it = source.find(property);
  if (it != source.end()) {
    ret = it.value().get<T>();
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
  } else if (required) {
    return 0;
  }
  return 1;
}

// bool GltfLoader::ParseString(
//     std::string& ret, const json& source, const char* property, bool
//     required) {
//   auto it = source.find(property);
//   if (it != source.end()) {
//     ret = it.value().get<std::string>();
//   } else if (required) {
//     return 0;
//   }
//   return 1;
// }
// bool ParseStringGltfIdDict(
//     std::map<std::string, GltfId>& ret, const json& source,
//     const char* property, bool required) {
//   auto it = source.find(property);
//   if (it != source.end()) {
//     for (auto id = it.value().begin(); id != it.value().end(); ++id) {
//       ret[id.key().c_str()] = id.value().get<GltfId>();
//     }
//   } else if (required) {
//     return 0;
//   }
//   return 1;
// }
// bool GltfLoader::ParseGltfId(
//     GltfId& ret, const json& source, const char* property, bool required) {
//   auto it = source.find(property);
//   if (it != source.end()) {
//     ret = it.value().get<GltfId>();
//   } else if (required) {
//     return 0;
//   }
//   return 1;
// }
// bool GltfLoader::ParseGltfIdArray(
//     std::vector<GltfId>& ret, const json& source, const char* property,
//     bool required) {
//   auto it = source.find(property);
//   ret.clear();
//   if (it != source.end()) {
//     for (auto id : it.value()) {
//       ret.push_back(id.get<GltfId>());
//     }
//   } else if (required) {
//     return 0;
//   }
//   return 1;
// }
// bool GltfLoader::ParseGltfInt(
//     GltfInt& ret, const json& source, const char* property, bool required) {
//   auto it = source.find(property);
//   if (it != source.end()) {
//     ret = it.value().get<GltfInt>();
//   } else if (required) {
//     return 0;
//   }
//   return 1;
// }
// bool GltfLoader::ParseGltfIntArray(
//     std::vector<GltfInt>& ret, const json& source, const char* property,
//     bool required) {
//   auto it = source.find(property);
//   ret.clear();
//   if (it != source.end()) {
//     for (auto id : it.value()) {
//       ret.push_back(id.get<GltfInt>());
//     }
//   } else if (required) {
//     return 0;
//   }
//   return 1;
// }
// bool GltfLoader::ParseGltfNum(
//     GltfNum& ret, const json& source, const char* property, bool required) {
//   auto it = source.find(property);
//   if (it != source.end()) {
//     ret = it.value().get<GltfNum>();
//   } else if (required) {
//     return 0;
//   }
//   return 1;
// }
// bool GltfLoader::ParseGltfNumArray(
//     std::vector<GltfNum>& ret, const json& source, const char* property,
//     bool required) {
//   auto it = source.find(property);
//   ret.clear();
//   if (it != source.end()) {
//     for (auto id : it.value()) {
//       ret.push_back(id.get<GltfNum>());
//     }
//   } else if (required) {
//     return 0;
//   }
//   return 1;
// }

}  // namespace kplgltf
}  // namespace kplge