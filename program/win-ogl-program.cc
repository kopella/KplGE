#include "win-ogl-application.h"

#include "kpl-log.h"

int main() {
  kplge::WinOglApplication* win_ogl_application =
      new kplge::WinOglApplication();
  log_to_console(
      info, "initialize result: {}", win_ogl_application->initialize());
  log_to_console(
      info, "show window result: {}", win_ogl_application->show_window());

  while (!win_ogl_application->check_quit_tag()) {
    win_ogl_application->tick();
  }

  log_to_console(info, "finalize result: {}", win_ogl_application->finalize());
  delete win_ogl_application;
  return 0;
}
