#include "scene-manager.h"
#include "scene-mesh.h"

using namespace kplge;

int main() {
  std::cout << "Scene Manager Test: " << std::endl;

  SceneManager* sceneManager = new SceneManager();
  sceneManager->LoadGltfFile(
      "test/mesh-test.gltf");
  return 0;
}