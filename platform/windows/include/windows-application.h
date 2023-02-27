#pragma once
#include <windows.h>

#include "base-application.h"

namespace kplge {
class WindowsApplication : public BaseApplication {
 public:
  erroc Initialize() override;
  erroc Finalize() override;
  erroc Tick() override;

  erroc ShowMainWindow();

  HWND GetMainWindowHandler() { return h_wnd_; }

 private:
  HINSTANCE h_inst_;
  HWND h_wnd_;

  bool CreateMainWindow();
  bool DestroyMainWindow();

  static LRESULT CALLBACK
  WindowProc(HWND h_wnd, UINT msg, WPARAM wparam, LPARAM lparam);
};
}  // namespace kplge
