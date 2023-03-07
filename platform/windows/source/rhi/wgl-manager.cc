#include "wgl-manager.h"

#include "windows-application.h"

namespace kplge {
erroc WglManager::Initialize() {
  if (!CreateContext()) return GFX_ERR_INIT;
  if (!GetFunctions()) return GFX_ERR_INIT;
  return KPL_NO_ERR;
}

erroc WglManager::Finalize() {
  if (!DeleteContext()) return GFX_ERR_FINA;
  return KPL_NO_ERR;
}

erroc WglManager::Tick() {
  if (!Draw()) return GFX_ERR_RUNT;
  SwapBuffers(h_gl_dc_);
  return KPL_NO_ERR;
}

bool WglManager::CreateContext() {
  PIXELFORMATDESCRIPTOR
  des_pf = {
      .nSize = sizeof(des_pf),
      .nVersion = 1,
      .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
      .iPixelType = PFD_TYPE_RGBA,
      .cColorBits = 32,
      .cAlphaBits = 8,
      .cDepthBits = 24,
      .cStencilBits = 8,
      .iLayerType = PFD_MAIN_PLANE,
  };

  h_gl_dc_ = GetDC(
      dynamic_cast<WindowsApplication*>(application_)->GetMainWindowHandler());
  int n_pf = ChoosePixelFormat(h_gl_dc_, &des_pf);
  if (!n_pf) return 0;

  if (!SetPixelFormat(h_gl_dc_, n_pf, &des_pf)) return 0;

  h_gl_rc_ = wglCreateContext(h_gl_dc_);
  if (!h_gl_rc_) return 0;

  if (!wglMakeCurrent(h_gl_dc_, h_gl_rc_)) return 0;

  return 1;
}

bool WglManager::DeleteContext() {
  if (!wglMakeCurrent(h_gl_dc_, 0)) return 0;
  if (!wglDeleteContext(h_gl_rc_)) return 0;
  if (!ReleaseDC(
          dynamic_cast<WindowsApplication*>(application_)
              ->GetMainWindowHandler(),
          h_gl_dc_))
    return 0;
  return 1;
}
}  // namespace kplge