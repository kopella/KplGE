#pragma once
#include "gfx-manager.h"

#if defined(_WIN32)
#include <windows.h>
#endif

#include "GL/gl.h"
#include "GL/glext.h"

namespace kplge {
class OglManager : public GfxManager {
 public:
  erroc initialize() override = 0;
  erroc finalize() override = 0;

  erroc tick() override = 0;

  /* OpenGL tool functions*/
  int draw_scene();

  GLuint load_shader();   // return shader program
  GLuint load_vertex();   // return vertex array object
  GLuint load_texture();  //

 private:
  virtual int get_functions() = 0;

  virtual int create_context() = 0;
  virtual int delete_context() = 0;

 protected:
  /* OpenGL functions pointers*/

  /* Program */
  PFNGLCREATEPROGRAMPROC glCreateProgram;
  PFNGLLINKPROGRAMPROC glLinkProgram;
  PFNGLUSEPROGRAMPROC glUseProgram;
  PFNGLDELETEPROGRAMPROC glDeleteProgram;
  PFNGLGETPROGRAMIVPROC glGetProgramiv;
  PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

  /* Shader */
  PFNGLCREATESHADERPROC glCreateShader;
  PFNGLSHADERSOURCEPROC glShaderSource;
  PFNGLCOMPILESHADERPROC glCompileShader;
  PFNGLATTACHSHADERPROC glAttachShader;
  PFNGLDETACHSHADERPROC glDetachShader;
  PFNGLDELETESHADERPROC glDeleteShader;
  PFNGLGETSHADERIVPROC glGetShaderiv;
  PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

  /* Vertex */
  PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
  PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
  PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
  PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
  PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
  PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

  /* Buffer */
  PFNGLGENBUFFERSPROC glGenBuffers;
  PFNGLBINDBUFFERPROC glBindBuffer;
  PFNGLBUFFERDATAPROC glBufferData;
  PFNGLDELETEBUFFERSPROC glDeleteBuffers;

  PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
  PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
  PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
  PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
  PFNGLUNIFORM1IPROC glUniform1i;
  PFNGLUNIFORM3FVPROC glUniform3fv;
  PFNGLUNIFORM4FVPROC glUniform4fv;

  PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
};
}  // namespace kplge