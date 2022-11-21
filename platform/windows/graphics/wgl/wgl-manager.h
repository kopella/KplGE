#pragma once
#include "ogl/ogl-manager.h"
#include "wgl-define.h"

namespace kplge {
class WglManager : public OglManager {
 public:
  ~WglManager() override = default;

  int initialize() override;
  int finalize() override;

  int tick() override;

 private:
  HGLRC h_gl_rc;

  HGLRC init_wgl(HDC h_dc);
  void kill_wgl(HINSTANCE h_inst, HWND h_wnd, HDC h_dc, HGLRC h_rc);
  int load_gl_func();

 public:
  PFNGLATTACHSHADERPROC glAttachShader;
  PFNGLBINDBUFFERPROC glBindBuffer;
  PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
  PFNGLBUFFERDATAPROC glBufferData;
  PFNGLCOMPILESHADERPROC glCompileShader;
  PFNGLCREATEPROGRAMPROC glCreateProgram;
  PFNGLCREATESHADERPROC glCreateShader;
  PFNGLDELETEBUFFERSPROC glDeleteBuffers;
  PFNGLDELETEPROGRAMPROC glDeleteProgram;
  PFNGLDELETESHADERPROC glDeleteShader;
  PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
  PFNGLDETACHSHADERPROC glDetachShader;
  PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
  PFNGLGENBUFFERSPROC glGenBuffers;
  PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
  PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
  PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
  PFNGLGETPROGRAMIVPROC glGetProgramiv;
  PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
  PFNGLGETSHADERIVPROC glGetShaderiv;
  PFNGLLINKPROGRAMPROC glLinkProgram;
  PFNGLSHADERSOURCEPROC glShaderSource;
  PFNGLUSEPROGRAMPROC glUseProgram;
  PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
  PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
  PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
  PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
  PFNGLACTIVETEXTUREPROC glActiveTexture;
  PFNGLUNIFORM1IPROC glUniform1i;
  PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
  PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
  PFNGLUNIFORM3FVPROC glUniform3fv;
  PFNGLUNIFORM4FVPROC glUniform4fv;
};
}  // namespace kplge