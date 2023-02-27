#pragma once
#include "opengl-manager.h"

namespace kplge {
class WglManager : public OpenGLManager {
 public:
  WglManager() = default;
  virtual ~WglManager() = default;

  erroc Initialize() override;
  erroc Finalize() override;
  erroc Tick() override;

 private:
  HDC h_gl_dc_;
  HGLRC h_gl_rc_;

  bool GetFunctions() override;
  bool CreateContext() override;
  bool DeleteContext() override;
};
}  // namespace kplge