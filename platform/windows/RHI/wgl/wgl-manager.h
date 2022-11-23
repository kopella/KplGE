#pragma once
#include "gfx-manager.h"
#include "win-ogl-application.h"

#include "wgl-define.h"

namespace kplge {
class WglManager : public GfxManager {
 public:
  WglManager(WinOglApplication* application);

  erroc initialize() override;
  erroc finalize() override;

  erroc tick() override;

 private:
  WinOglApplication* win_ogl_application;
  HGLRC h_gl_rc;
  HDC h_dc;

  int init_wgl();
  int load_gl_func();

  int kill_wgl();

  GLuint shader_prog;
  GLuint v_array_obj;

  GLuint load_shader();
  GLuint load_vertex();

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