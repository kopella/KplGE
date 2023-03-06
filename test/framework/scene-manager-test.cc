#include "scene-manager.h"
#include "scene-mesh.h"

using namespace kplge;

int main() {
  SceneManager* sceneManager = new SceneManager();
  sceneManager->LoadGltfFile("test/AntiqueCamera/AntiqueCamera.gltf");
  std::cout << "Scene Manager Test: " << std::endl;
  std::cout << *sceneManager;
  delete sceneManager;
  return 0;
}