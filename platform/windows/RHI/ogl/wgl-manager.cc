#include "wgl-manager.h"

int kplge::WglManager::init_wgl(HDC h_dc) {
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

  int n_pf = ChoosePixelFormat(h_dc, &des_pf);
  if (!n_pf) {
    // Failed to find a suitable pixel format.
    return 0;
  }
  if (!SetPixelFormat(h_dc, n_pf, &des_pf)) {
    // Failed to set the pixel format.");
    return 0;
  }
  HGLRC h_rc = wglCreateContext(h_dc);
  if (!h_rc) {
    // Failed to create a OpenGL rendering context.
    return 0;
  }
  if (!wglMakeCurrent(h_dc, h_rc)) {
    // Failed to activate the OpenGL rendering context.
    return 0;
  }
  if (!load_gl_func()) {
    // Failed to load OpenGL's function.
    return 0;
  }
  return 1;
}

int kplge::WglManager::kill_wgl(
    HINSTANCE h_inst, HWND h_wnd, HDC h_dc, HGLRC h_rc) {
  if (!wglMakeCurrent(h_dc, 0)) {
    // Failed to detach the rendering context.
    return 0;
  }
  if (!wglDeleteContext(h_rc)) {
    // Failed to delete the rendering context.
    return 0;
  }
  return 1;
}

int kplge::WglManager::load_gl_func() {
  glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
  if (!glAttachShader) {
    return 0;
  }
  glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
  if (!glBindBuffer) {
    return 0;
  }
  glBindVertexArray =
      (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
  if (!glBindVertexArray) {
    return 0;
  }
  glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
  if (!glBufferData) {
    return 0;
  }
  glCompileShader =
      (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
  if (!glCompileShader) {
    return 0;
  }
  glCreateProgram =
      (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
  if (!glCreateProgram) {
    return 0;
  }
  glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
  if (!glCreateShader) {
    return 0;
  }
  glDeleteBuffers =
      (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
  if (!glDeleteBuffers) {
    return 0;
  }
  glDeleteProgram =
      (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
  if (!glDeleteProgram) {
    return 0;
  }
  glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
  if (!glDeleteShader) {
    return 0;
  }
  glDeleteVertexArrays =
      (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
  if (!glDeleteVertexArrays) {
    return 0;
  }
  glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
  if (!glDetachShader) {
    return 0;
  }
  glEnableVertexAttribArray =
      (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress(
          "glEnableVertexAttribArray");
  if (!glEnableVertexAttribArray) {
    return 0;
  }
  glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
  if (!glGenBuffers) {
    return 0;
  }
  glGenVertexArrays =
      (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
  if (!glGenVertexArrays) {
    return 0;
  }
  glGetAttribLocation =
      (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
  if (!glGetAttribLocation) {
    return 0;
  }
  glGetProgramInfoLog =
      (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
  if (!glGetProgramInfoLog) {
    return 0;
  }
  glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
  if (!glGetProgramiv) {
    return 0;
  }
  glGetShaderInfoLog =
      (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
  if (!glGetShaderInfoLog) {
    return 0;
  }
  glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
  if (!glGetShaderiv) {
    return 0;
  }
  glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
  if (!glLinkProgram) {
    return 0;
  }
  glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
  if (!glShaderSource) {
    return 0;
  }
  glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
  if (!glUseProgram) {
    return 0;
  }
  glVertexAttribPointer =
      (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
  if (!glVertexAttribPointer) {
    return 0;
  }
  glBindAttribLocation =
      (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
  if (!glBindAttribLocation) {
    return 0;
  }
  glGetUniformLocation =
      (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
  if (!glGetUniformLocation) {
    return 0;
  }
  glUniformMatrix4fv =
      (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
  if (!glUniformMatrix4fv) {
    return 0;
  }
  glActiveTexture =
      (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
  if (!glActiveTexture) {
    return 0;
  }
  glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
  if (!glUniform1i) {
    return 0;
  }
  glGenerateMipmap =
      (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
  if (!glGenerateMipmap) {
    return 0;
  }
  glDisableVertexAttribArray =
      (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress(
          "glDisableVertexAttribArray");
  if (!glDisableVertexAttribArray) {
    return 0;
  }
  glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
  if (!glUniform3fv) {
    return 0;
  }
  glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
  if (!glUniform4fv) {
    return 0;
  }
  return 1;
}