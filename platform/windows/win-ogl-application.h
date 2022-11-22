#pragma once
#include <windows.h>
#include <windowsx.h>

#include "base-application.h"
#include "gfx-manager.h"

namespace kplge {
class WinOglApplication : public BaseApplication {
 public:
  erroc initialize() override;
  erroc finalize() override;

  erroc tick() override;

  erroc show_window();

 private:
  GfxManager* gfx_manager;

  HINSTANCE h_inst;
  HWND h_wnd;
  HDC h_dc;

  int create_window();
  int destroy_window();

  static LRESULT CALLBACK
  wnd_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
}  // namespace kplge
