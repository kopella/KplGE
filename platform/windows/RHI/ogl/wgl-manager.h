#pragma once
#include "gfx-manager.h"
#include "win-ogl-application.h"

namespace kplge {
class WglManager : public GfxManager {
 public:
  WglManager(WinOglApplication* application);

  erroc initialize() override;
  erroc finalize() override;

  erroc tick() override;

 private:
  WinOglApplication* application;

  HGLRC h_gl_rc;
  HDC h_dc;

  int get_functions();

  int create_context();
  int delete_context();

};
}  // namespace kplge