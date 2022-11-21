#pragma once
#include <windows.h>
#include <windowsx.h>

#include "base-application.h"
#include "wgl/wgl-manager.h"

namespace kplge {
class WinOglApplication : public BaseApplication {
 public:
  int initialize() override;
  int finalize() override;

  int tick() override;

 private:
  WglManager* wgl_manager;

  HINSTANCE h_inst;
  HWND h_wnd;
  HDC h_dc;

  void create_window();
  static LRESULT CALLBACK
  wnd_proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
}  // namespace kplge
