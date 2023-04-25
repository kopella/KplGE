#include <cstdio>

#include "windows-application.h"
#include "wgl-manager.h"
#include "scene-manager.h"
#include "kpllogt.h"

using namespace kplge;

int main() {
  WindowsApplication* windowsApplication = new WindowsApplication();
  GraphicManager* wglManager = new WglManager();
  SceneManager* sceneManager = new SceneManager();

  windowsApplication->RegisterManager(wglManager);
  windowsApplication->RegisterManager(sceneManager);

  sceneManager->LoadGltfFile("test/mesh-test.gltf");

  std::cout << *sceneManager;

  erroc code = KPL_NO_ERR;

  code = windowsApplication->Initialize();
  runtime_info("WindowsApplication", "Initialize result: %x\n", code);

  windowsApplication->ShowMainWindow();
  while (!windowsApplication->CheckQuitTag()) {
    windowsApplication->Tick();
  }

  code = windowsApplication->Finalize();
  runtime_info("WindowsApplication", "Finalize result: %x\n", code);

  delete windowsApplication;
  return 0;
}
