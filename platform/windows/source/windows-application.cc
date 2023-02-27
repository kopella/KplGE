#include "../include/windows-application.h"

namespace kplge {
erroc WindowsApplication::Initialize() {
  BaseApplication::Initialize();
  if (!CreateMainWindow()) return WIN_ERR_CWND;

  for (auto manager : managers) {
    erroc code = manager->Initialize();
    if (code != KPL_NO_ERR) return code;
  }
  return KPL_NO_ERR;
}

erroc WindowsApplication::Finalize() {
  for (auto manager : managers) {
    erroc code = manager->Finalize();
    if (code != KPL_NO_ERR) return code;
  }
  if (!DestroyMainWindow()) return WIN_ERR_DWND;
  BaseApplication::Finalize();
  return KPL_NO_ERR;
}

erroc WindowsApplication::Tick() {
  BaseApplication::Tick();
  MSG msg;
  if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
    if (msg.message == WM_QUIT) {
      ChangeQuitTag();
      return KPL_NO_ERR;
    } else {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  for (auto manager : managers) {
    erroc code = manager->Tick();
    if (code != KPL_NO_ERR) return code;
  }
  return KPL_NO_ERR;
}

erroc WindowsApplication::ShowMainWindow() {
  ShowWindow(h_wnd_, SW_SHOW);
  UpdateWindow(h_wnd_);
  return KPL_NO_ERR;
}

bool WindowsApplication::CreateMainWindow() {
  h_inst_ = GetModuleHandle(0);
  WNDCLASS wnd_class = {
      .style = CS_HREDRAW | CS_VREDRAW,
      .lpfnWndProc = WindowProc,
      .hInstance = h_inst_,
      .hCursor = LoadCursor(0, IDC_ARROW),
      .hbrBackground = 0,
      .lpszClassName = "WGL Application",
  };
  if (!RegisterClass(&wnd_class)) return 0;
  RECT rect = {
      .right = 960,
      .bottom = 540,
  };
  AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
  h_wnd_ = CreateWindow(
      wnd_class.lpszClassName, "WGL Application", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left,
      rect.bottom - rect.top, 0, 0, h_inst_, 0);
  if (!h_wnd_) return 0;
  return 1;
}

bool WindowsApplication::DestroyMainWindow() {
  if (!DestroyWindow(h_wnd_)) return 0;
  if (!UnregisterClass("WGL Application", h_inst_)) return 0;
  return 1;
}

LRESULT CALLBACK WindowsApplication::WindowProc(
    HWND h_wnd_, UINT msg, WPARAM w_param, LPARAM l_param) {
  LRESULT result = 0;
  switch (msg) {
    case WM_CLOSE:
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    case WM_SIZE:
      // MyReSizeGLScene(LOWORD(l_param), HIWORD(l_param));
      break;
    default:
      result = DefWindowProcA(h_wnd_, msg, w_param, l_param);
      break;
  }
  return result;
}
}  // namespace kplge