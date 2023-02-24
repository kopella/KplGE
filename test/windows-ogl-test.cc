#include "kpl-config.h"
#include "win-ogl-application.h"

#include "kpl-log.h"

#include <cstdio>

using namespace kplge;

int main() {
  WinOglApplication* win_ogl_application = new WinOglApplication();

  erroc code = KPL_NO_ERR;

  code = win_ogl_application->initialize();
  printf("initialize result: %x\n", code);

  win_ogl_application->show_window();
  while (!win_ogl_application->check_quit_tag()) {
    win_ogl_application->tick();
  }

  code = win_ogl_application->finalize();
  printf("finalize result: %x\n", code);

  delete win_ogl_application;
  return 0;
}
