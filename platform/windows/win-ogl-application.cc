#include "RHI/wgl/wgl-manager.h"
#include "base-application.h"
#include "win-ogl-application.h"

erroc kplge::WinOglApplication::initialize() {
  BaseApplication::initialize();
  if (!create_window()) {
    return WIN_ERR_CWND;
  }
  gfx_manager = new kplge::WglManager(this);

  erroc code = gfx_manager->initialize();
  if (code != KPL_NO_ERR) {
    return code;
  }
  return KPL_NO_ERR;
}

erroc kplge::WinOglApplication::finalize() {
  erroc code = gfx_manager->finalize();
  if (code != KPL_NO_ERR) {
    return code;
  }

  if (!destroy_window()) {
    return WIN_ERR_DWND;
  }
  BaseApplication::finalize();
  return KPL_NO_ERR;
}

erroc kplge::WinOglApplication::tick() {
  BaseApplication::tick();
  MSG msg;
  if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
    if (msg.message == WM_QUIT) {
      change_quit_tag();
      return KPL_NO_ERR;
    } else {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  erroc code = gfx_manager->tick();
  if (code != KPL_NO_ERR) {
    return code;
  }
  return KPL_NO_ERR;
}

erroc kplge::WinOglApplication::show_window() {
  ShowWindow(h_wnd, SW_SHOW);
  UpdateWindow(h_wnd);
  return KPL_NO_ERR;
}

int kplge::WinOglApplication::create_window() {
  h_inst = GetModuleHandle(0);

  WNDCLASS wnd_class = {
      .style = CS_HREDRAW | CS_VREDRAW,
      .lpfnWndProc = wnd_proc,
      .hInstance = h_inst,
      .hCursor = LoadCursor(0, IDC_ARROW),
      .hbrBackground = 0,
      .lpszClassName = "WGL Application",
  };

  if (!RegisterClass(&wnd_class)) {
    return 0;
  }

  RECT rect = {
      .right = 960,
      .bottom = 540,
  };
  AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);

  h_wnd = CreateWindow(
      wnd_class.lpszClassName, "WGL Application", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left,
      rect.bottom - rect.top, 0, 0, h_inst, 0);

  if (!h_wnd) {
    return WIN_ERR_CWND;
  }
  return 1;
}

int kplge::WinOglApplication::destroy_window() {
  if (!DestroyWindow(h_wnd)) {
    // Failed to destroy the window.
    return 0;
  }
  if (!UnregisterClass("WGL Application", h_inst)) {
    // Failed to unregister the class.
    return 0;
  }
  return 1;
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
