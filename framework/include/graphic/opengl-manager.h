#pragma once
#include "graphic-manager.h"
#include "scene-node.h"

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

  bool Clear() override;
  bool Draw() override;

  GLuint LoadShader();
  GLuint LoadVertex();

 private:
  virtual bool GetFunctions() = 0;
  virtual bool CreateContext() = 0;
  virtual bool DeleteContext() = 0;

  bool InitializeShaders(const char* vsFile, const char* fsFile);
  bool InitializeBuffers();

  bool RenderBuffers();

  bool SetPerBatchShaderParameters(
      const char* paramName, const Matrix4X4f& param);

  bool LoadNode(SceneNode& node);
  bool LoadMeshNode(SceneMeshNode& node);

 private:
  GLuint vertexShader_;
  GLuint fragmentShader_;
  GLuint shaderProgram_;
  std::vector<GLuint> buffers_;

  struct DrawBatchContext {
    GLuint vao;
    GLsizei count;
    GLenum mode;
    GLenum indices_type;
    Matrix4X4f transform;
  };

  std::vector<DrawBatchContext> drawBatchContexts_;

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