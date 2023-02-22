#pragma once
#include "ogl/ogl-manager.h"
#include "win-ogl-application.h"

namespace kplge {
class WglManager : public OglManager {
 public:
  WglManager() = default;
  explicit WglManager(WinOglApplication* application);
  virtual ~WglManager() = default;

  erroc initialize() override;
  erroc finalize() override;

  erroc tick() override;

 private:
  WinOglApplication* p_application;

  HDC h_dc;
  HGLRC h_gl_rc;

  int get_functions() override;

  int create_context() override;
  int delete_context() override;
};
}  // namespace kplge