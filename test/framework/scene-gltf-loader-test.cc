#include "scene-loader/gltf-loader.h"

#include <iostream>

#include "kpllogt.h"

using namespace kplge::kplgltf;

int main() {
  GltfLoader gltfLoader;

  test_info("GltfLoaderTest", "Test case 1: \n");
  GLtfContainer gLtfContainer_1{};
  if (!gltfLoader.ParseGltfFile(gLtfContainer_1, "test/mesh-test.gltf"))
    std::cout << "Failed to parse file";
  else
    std::cout << gLtfContainer_1;

  test_info("GltfLoaderTest", "Test case 2: \n");
  GLtfContainer gLtfContainer_2{};
  if (!gltfLoader.ParseGltfFile(
          gLtfContainer_2, "test/A Minimal glTF File/A Minimal glTF File.gltf"))
    std::cout << "Failed to parse file";
  else
    std::cout << gLtfContainer_2;

  return 0;
}