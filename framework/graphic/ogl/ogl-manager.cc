#include "ogl-manager.h"

#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

int kplge::OglManager::draw_scene() {
  glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  GLuint shader_prog = load_shader();
  GLuint v_array_obj = load_vertex();

  glUseProgram(shader_prog);
  glBindVertexArray(v_array_obj);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  return 1;
}


GLuint kplge::OglManager::load_shader() {
  const char* v_shader_path = "../../asset/shader/v_shader.glsl";
  const char* f_shader_path = "../../asset/shader/f_shader.glsl";

  std::string v_shader_code;
  std::string f_shader_code;
  std::ifstream v_shader_file;
  std::ifstream f_shader_file;

  v_shader_file.open(v_shader_path);
  f_shader_file.open(f_shader_path);

  std::stringstream v_shader_st, f_shader_st;

  v_shader_st << v_shader_file.rdbuf();
  f_shader_st << f_shader_file.rdbuf();

  v_shader_file.close();
  f_shader_file.close();

  v_shader_code = v_shader_st.str();
  f_shader_code = f_shader_st.str();

  const char* v_shader_src = v_shader_code.c_str();
  const char* f_shader_src = f_shader_code.c_str();

  GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(v_shader, 1, &v_shader_src, 0);
  glCompileShader(v_shader);

  GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(f_shader, 1, &f_shader_src, 0);
  glCompileShader(f_shader);

  GLuint shader_prog = glCreateProgram();
  glAttachShader(shader_prog, v_shader);
  glAttachShader(shader_prog, f_shader);
  glLinkProgram(shader_prog);

  glDeleteShader(v_shader);
  glDeleteShader(f_shader);

  return shader_prog;
}

GLuint kplge::OglManager::load_vertex() {
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

GLuint kplge::OglManager::load_texture() { return 0; }