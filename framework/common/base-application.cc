#include "base-application.h"
#include "kpl-log.h"

erroc kplge::BaseApplication::initialize() {
  quit_tag = false;
  /*
  for (IManager* manager : managers) {
    if ((manager->initialize()) != 0) {
      log_to_console(error, "Manager initialize failed");
    }
  }
  */
  return KPL_NO_ERR;
}

erroc kplge::BaseApplication::finalize() { return KPL_NO_ERR; }

erroc kplge::BaseApplication::tick() { return KPL_NO_ERR; }

bool kplge::BaseApplication::check_quit_tag() { return quit_tag; }

void kplge::BaseApplication::change_quit_tag() { quit_tag = true; }