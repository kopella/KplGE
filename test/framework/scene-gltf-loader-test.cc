#include "gltf-loader.h"

#include <iostream>

using namespace kplge::kplgltf;

int main() {
  GltfLoader gltfLoader;
  GLtfContainer gLtfContainer = gltfLoader.ParseGltfFile("test/AnimatedMorphSphere/AnimatedMorphSphere.gltf");
  std::cout << gLtfContainer;
  return 0;
}