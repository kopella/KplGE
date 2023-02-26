#include "wgl-manager.h"

#include "kpl-config.h"
#include "kpl-log.h"

kplge::WglManager::WglManager(WinOglApplication* application) {
  this->p_application = application;
}

kplge::erroc kplge::WglManager::initialize() {
  if (!create_context()) return GFX_ERR_INIT;
  if (!get_functions()) return GFX_ERR_INIT;
  return KPL_NO_ERR;
}

kplge::erroc kplge::WglManager::finalize() {
  if (!delete_context()) return GFX_ERR_FINA;
  return KPL_NO_ERR;
}

kplge::erroc kplge::WglManager::tick() {
  if (!draw_scene()) return GFX_ERR_RUNT;
  SwapBuffers(h_dc);
  return KPL_NO_ERR;
}

int kplge::WglManager::create_context() {
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

  h_dc = GetDC(p_application->h_wnd);
  int n_pf = ChoosePixelFormat(h_dc, &des_pf);
  if (!n_pf) return 0;

  if (!SetPixelFormat(h_dc, n_pf, &des_pf)) return 0;

  h_gl_rc = wglCreateContext(h_dc);
  if (!h_gl_rc) return 0;

  if (!wglMakeCurrent(h_dc, h_gl_rc)) return 0;

  return 1;
}

int kplge::WglManager::delete_context() {
  if (!wglMakeCurrent(h_dc, 0)) return 0;

  if (!wglDeleteContext(h_gl_rc)) return 0;

  if (!ReleaseDC(p_application->h_wnd, h_dc)) return 0;

  return 1;
}