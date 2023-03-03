#include "gltf-loader.h"

#include <map>
#include <memory>
#include <string>
#include <iostream>

#include "kpllogt.h"

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
  for (auto& val : source) {
    Scene scene;

    ParseValue<std::string>(scene.name, val, "name");

    ParseValueArray<GltfId>(scene.nodes, val, "nodes", true);

    gLtfContainer.scenes.emplace_back(std::move(scene));
  }
  return 1;
}

bool GltfLoader::ParseNodes(GLtfContainer& gLtfContainer, json& source) {
  for (auto& val : source) {
    Node node;

    ParseValue<std::string>(node.name, val, "name");

    ParseValueArray<GltfId>(node.children, val, "children");

    ParseValue<GltfId>(node.mesh, val, "mesh");

    ParseValue<GltfId>(node.skin, val, "skin");

    std::vector<GltfNum> matrix;
    ParseValueArray<GltfNum>(matrix, val, "matrix");
    if (matrix.empty()) {
      std::vector<GltfNum> rotation;
      ParseValueArray<GltfNum>(rotation, val, "rotation");
      std::vector<GltfNum> scale;
      ParseValueArray<GltfNum>(scale, val, "scale");
      std::vector<GltfNum> translation;
      ParseValueArray<GltfNum>(translation, val, "translation");
    } else {
      node.matrix = std::move(matrix);
    }

    ParseValueArray<GltfNum>(node.weights, val, "weights");

    gLtfContainer.nodes.emplace_back(std::move(node));
  }
  return 1;
}

bool GltfLoader::ParseMeshes(GLtfContainer& gLtfContainer, json& source) {
  for (auto& val : source) {
    Mesh mesh;

    ParseValue<std::string>(mesh.name, val, "name");

    ParsePrimitives(mesh, source);

    ParseValueArray<GltfNum>(mesh.weights, val, "weights");

    gLtfContainer.meshes.emplace_back(std::move(mesh));
  }
  return 1;
}

bool GltfLoader::ParsePrimitives(Mesh& mesh, json& source) {
  auto it = source.find("primitives");
  if (it != source.end()) {
    for (auto obj : it.value()) {
      Primitive primitive;
      ParseValueDict<GltfId>(primitive.attributes, obj, "attributes");

      ParseValue<GltfId>(primitive.indices, obj, "indices");

      ParseValue<GltfId>(primitive.material, obj, "material");

      GltfInt mode;
      ParseValue<GltfInt>(mode, source, "mode");
      primitive.mode = static_cast<PrimitiveMode>(mode);

      auto targets = obj.find("targets");
      if (it != source.end()) {
        for (auto id : it.value()) {
          std::map<std::string, GltfId> target;
          for (auto target_it = id.begin(); target_it != id.end();
               target_it++) {
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