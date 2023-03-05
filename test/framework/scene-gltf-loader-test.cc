#include "scene-loader/gltf-loader.h"

#include <iostream>

using namespace kplge::kplgltf;

int main() {
  GltfLoader gltfLoader;
  GLtfContainer gLtfContainer{};
  if (!gltfLoader.ParseGltfFile(
          gLtfContainer, "test/mesh-test.gltf"))
    std::cout << "Failed to parse file";
  else
    std::cout << gLtfContainer;
  return 0;
}