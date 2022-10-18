#include "base-application.h"
#include "kpl-log.h"

kplge::BaseApplication::BaseApplication(GraphicsConfiguration& gfx_config_)
    : gfx_config_(gfx_config_) {
  quit_tag = false;
}

int kplge::BaseApplication::initialize() {
  for (IManager* manager : managers) {
    if ((manager->initialize()) != 0) {
      log_to_console(error, "Manager initialize failed");
    }
  }
  return 0;
}