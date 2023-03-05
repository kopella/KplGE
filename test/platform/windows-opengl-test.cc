#include <cstdio>

#include "windows-application.h"
#include "wgl-manager.h"
#include "scene-manager.h"
#include "kpllogt.h"

using namespace kplge;

int main() {
  WindowsApplication* windows_application = new WindowsApplication();
  GraphicManager* wgl_manager = new WglManager();

  windows_application->RegisterManager(wgl_manager);

  erroc code = KPL_NO_ERR;

  code = windows_application->Initialize();
  runtime_info("WindowsApplication", "Initialize result: %x\n", code);

  windows_application->ShowMainWindow();
  while (!windows_application->CheckQuitTag()) {
    windows_application->Tick();
  }

  code = windows_application->Finalize();
  runtime_info("WindowsApplication", "Finalize result: %x\n", code);

  delete windows_application;
  return 0;
}
