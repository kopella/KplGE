#pragma once
#include "graphic-manager.h"

#if defined(_WIN32)
#include <windows.h>
#endif

#include "GL/gl.h"
#include "GL/glext.h"

namespace kplge {
class OpenGLManager : public GraphicManager {
 public:
  erroc Initialize() override;
  erroc Finalize() override;
  erroc Tick() override;

  /* OpenGL tool functions*/
  int DrawScene();

  GLuint LoadShader();
  GLuint LoadVertex();
  GLuint LoadTexture();

 private:
  virtual int GetFunctions() = 0;
  virtual int CreateContext() = 0;
  virtual int DeleteContext() = 0;

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