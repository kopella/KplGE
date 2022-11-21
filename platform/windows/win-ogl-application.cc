#include "win-ogl-application.h"
#include "base-application.h"

#include "kpl-log.h"

int kplge::WinOglApplication::initialize() {
  BaseApplication::initialize();
  create_window();
  return 0;
}

int kplge::WinOglApplication::finalize() {
  BaseApplication::finalize();
  if (!ReleaseDC(h_wnd, h_dc)) {
    log_to_console(error, "Failed to release the device context.");
  }
  if (!DestroyWindow(h_wnd)) {
    log_to_console(error, "Failed to destroy the window.");
  }
  if (!UnregisterClass("WGL Application", h_inst)) {
    log_to_console(error, "Failed to unregister the class.");
  }
  return 0;
}

int kplge::WinOglApplication::tick() {
  BaseApplication::tick();
  MSG msg;
  if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}

void kplge::WinOglApplication::create_window() {
  h_inst = GetModuleHandle(0);

  WNDCLASS wnd_class = {
      .style = CS_HREDRAW | CS_VREDRAW,
      .lpfnWndProc = wnd_proc,
      .hInstance = h_inst,
      .hCursor = LoadCursor(0, IDC_ARROW),
      .hbrBackground = 0,
      .lpszClassName = "WGL Application",
  };

  RegisterClass(&wnd_class);

  RECT rect = {
      .right = 960,
      .bottom = 540,
  };
  AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);

  h_wnd = CreateWindow(
      wnd_class.lpszClassName, "WGL Application", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left,
      rect.bottom - rect.top, 0, 0, h_inst, 0);

  h_dc = GetDC(h_wnd);
}

LRESULT CALLBACK kplge::WinOglApplication::wnd_proc(
    HWND h_wnd, UINT msg, WPARAM w_param, LPARAM l_param) {
  LRESULT result = 0;

  switch (msg) {
    case WM_CLOSE:
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    case WM_SIZE:
      //   MyReSizeGLScene(LOWORD(l_param), HIWORD(l_param));
      break;
    default:
      result = DefWindowProcA(h_wnd, msg, w_param, l_param);
      break;
  }

  return result;
}
