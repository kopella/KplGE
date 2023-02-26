#include "base-application.h"
#include "kpl-log.h"

kplge::erroc kplge::BaseApplication::initialize() {
  quit_tag = false;
  return KPL_NO_ERR;
}

kplge::erroc kplge::BaseApplication::finalize() { return KPL_NO_ERR; }

kplge::erroc kplge::BaseApplication::tick() { return KPL_NO_ERR; }

bool kplge::BaseApplication::check_quit_tag() { return quit_tag; }

void kplge::BaseApplication::change_quit_tag() { quit_tag = true; }