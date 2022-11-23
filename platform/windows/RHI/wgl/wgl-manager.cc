#include "wgl-manager.h"
#include <winuser.h>

kplge::WglManager::WglManager(WinOglApplication* application) {
  win_ogl_application = application;
}

erroc kplge::WglManager::initialize() {
  if (!init_wgl()) {
    return GFX_ERR_INIT;
  }

  shader_prog = load_shader();
  v_array_obj = load_vertex();

  return KPL_NO_ERR;
}

erroc kplge::WglManager::finalize() {
  if (!kill_wgl()) {
    return GFX_ERR_FINA;
  }
  return KPL_NO_ERR;
}

erroc kplge::WglManager::tick() {
  glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shader_prog);
  glBindVertexArray(v_array_obj);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  SwapBuffers(h_dc);

  return KPL_NO_ERR;
}

int kplge::WglManager::init_wgl() {
  h_dc = GetDC(win_ogl_application->h_wnd);
  if (!h_dc) {
    // Failed to get a handle of device context.
    return 0;
  }

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

int kplge::WglManager::kill_wgl() {
  if (!wglMakeCurrent(h_dc, 0)) {
    // Failed to detach the rendering context.
    return 0;
  }
  if (!wglDeleteContext(h_gl_rc)) {
    // Failed to delete the rendering context.
    return 0;
  }
  if (!ReleaseDC(win_ogl_application->h_wnd, h_dc)) {
    // Failed to release the device context.
    return 0;
  }
  return 1;
}

#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_TEXTURE0 0x84C0
#define GL_BGRA 0x80E1
#define GL_ELEMENT_ARRAY_BUFFER 0x8893

GLuint kplge::WglManager::load_shader() {
  const char* v_shader_src =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";
  const char* f_shader_src =
      "#version 330 core\n"
      "out vec4 FragColor;\n"
      "void main()\n"
      "{\n"
      "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}\n\0";

  GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(v_shader, 1, &v_shader_src, NULL);
  glCompileShader(v_shader);

  GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(f_shader, 1, &f_shader_src, NULL);
  glCompileShader(f_shader);

  GLuint shader_prog = glCreateProgram();
  glAttachShader(shader_prog, v_shader);
  glAttachShader(shader_prog, f_shader);
  glLinkProgram(shader_prog);

  glDeleteShader(v_shader);
  glDeleteShader(f_shader);

  return shader_prog;
}

GLuint kplge::WglManager::load_vertex() {
  float vertices[] = {
      -0.5f, -0.5f, 0.0f,  // left
      0.5f,  -0.5f, 0.0f,  // right
      0.0f,  0.5f,  0.0f   // top
  };

  GLuint v_buffer_obj, v_array_obj;
  glGenVertexArrays(1, &v_array_obj);
  glGenBuffers(1, &v_buffer_obj);

  glBindVertexArray(v_array_obj);

  glBindBuffer(GL_ARRAY_BUFFER, v_buffer_obj);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  return v_array_obj;
}