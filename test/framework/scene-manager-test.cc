#include "scene-manager.h"
#include "scene-mesh.h"

#include "kpllogt.h"

using namespace kplge;

int main() {
  test_info("SceneManagerTest", "Test case 1: \n");
  SceneManager* sceneManager_1 = new SceneManager();
  sceneManager_1->LoadGltfFile("test/mesh-test.gltf");
  std::cout << *sceneManager_1;
  delete sceneManager_1;

  test_info("SceneManagerTest", "Test case 2: \n");
  SceneManager* sceneManager_2 = new SceneManager();
  sceneManager_2->LoadGltfFile(
      "test/A Minimal glTF File/A Minimal glTF File.gltf");
  std::cout << *sceneManager_2;
  delete sceneManager_2;
  return 0;
}
