#include "opengl-manager.h"

#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

#include "asset-loader.h"
#include "scene-manager.h"

namespace kplge {
erroc OpenGLManager::Initialize() {
  // Set the depth buffer to be entirely cleared to 1.0 values.
  glClearDepth(1.0f);

  // Enable depth testing.
  glEnable(GL_DEPTH_TEST);

  // Set the polygon winding to front facing for the right handed system.
  glFrontFace(GL_CCW);

  // Enable back face culling.
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  
  InitializeShaders("v_shader.glsl", "f_shader.glsl");
  InitializeBuffers();
  return KPL_NO_ERR;
}
erroc OpenGLManager::Finalize() { return KPL_NO_ERR; }
erroc OpenGLManager::Tick() {
  if (!Draw()) return GFX_ERR_RUNT;
  return KPL_NO_ERR;
}

bool OpenGLManager::Draw() {
  glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shaderProgram_);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  return 1;
}

bool OpenGLManager::Clear() {
  // Set the color to clear the screen to.
  glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
  // Clear the screen and depth buffer.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  return 1;
}

bool OpenGLManager::InitializeShaders(const char* vsFile, const char* fsFile) {
  AssetLoader assetLoader;
  assetLoader.AddSearchPath("asset/shader/");
  std::string vertexShaderBuffer{reinterpret_cast<char*>(
      assetLoader.SyncLoadText(vsFile).get_data_pointer())};
  if (vertexShaderBuffer.empty()) return 0;
  std::string fragmentShaderBuffer{reinterpret_cast<char*>(
      assetLoader.SyncLoadText(fsFile).get_data_pointer())};
  if (fragmentShaderBuffer.empty()) return 0;

  vertexShader_ = glCreateShader(GL_VERTEX_SHADER);
  fragmentShader_ = glCreateShader(GL_FRAGMENT_SHADER);

  const char* _v_c_str = vertexShaderBuffer.c_str();
  glShaderSource(vertexShader_, 1, &_v_c_str, NULL);
  const char* _f_c_str = fragmentShaderBuffer.c_str();
  glShaderSource(fragmentShader_, 1, &_f_c_str, NULL);

  glCompileShader(vertexShader_);
  glCompileShader(fragmentShader_);

  shaderProgram_ = glCreateProgram();

  glAttachShader(shaderProgram_, vertexShader_);
  glAttachShader(shaderProgram_, fragmentShader_);

  glLinkProgram(shaderProgram_);

  return 1;
}

bool OpenGLManager::InitializeBuffers() {
  auto& root = p_sceneManager_->GetSceneRenderRoot(0);
  LoadNode(root);
  return 1;
}

bool OpenGLManager::RenderBuffers() {
  for (auto dbc : drawBatchContexts_) {
    glBindVertexArray(dbc.vao);
  }

  return 1;
}

bool OpenGLManager::LoadNode(SceneNode& node) {
  for (auto& child : node.GetChildren()) {
    if (!child.GetChildren().empty()) {
      LoadNode(child);
    }
  }
  for (auto& meshNode : node.GetMeshNodes()) {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    LoadMeshNode(meshNode);
    DrawBatchContext dbc;
    dbc.vao = vao;
    dbc.transform = meshNode.GetTransformMatrix();
    drawBatchContexts_.emplace_back(std::move(dbc));
  }
  return 1;
}

bool OpenGLManager::LoadMeshNode(SceneMeshNode& node) {
  auto mesh = node.GetMesh();
  for (auto indexArray : mesh->GetIndexArraies()) {
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, indexArray.GetData().size(),
        &indexArray.GetData().front(), GL_STATIC_DRAW);

    buffers_.push_back(ebo);
  }
  for (auto vertexArray : mesh->GetVertexArraies()) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
        GL_ARRAY_BUFFER, vertexArray.GetData().size(),
        &vertexArray.GetData().front(), GL_STATIC_DRAW);

    buffers_.push_back(vbo);

    GLuint vaa;
    switch (vertexArray.attribute_) {
      case VertexAttribute::POSITION:
        vaa = 0;
        break;
      case VertexAttribute::NORMAL:
        vaa = 1;
        break;
      case VertexAttribute::TEXCOORD:
        vaa = 2;
        break;
      case VertexAttribute::TANGENT:
        vaa = 3;
        break;
        break;
    }

    GLuint size;
    switch (vertexArray.dataType_) {
      case DataType::VEC2F:
        size = 2;
        break;
      case DataType::VEC3F:
        size = 3;
        break;
      case DataType::VEC4F:
        size = 4;
        break;
    }

    glEnableVertexAttribArray(vaa);
    glVertexAttribPointer(vaa, size, GL_FLOAT, GL_TRUE, 0, (void*)0);
  }

  if (!node.GetMeshNodes().empty()) {
    for (auto& meshNode : node.GetMeshNodes()) {
      LoadMeshNode(meshNode);
    }
  }
  return 1;
}

GLuint OpenGLManager::LoadShader() {
  const char* v_shader_path = "../../../asset/shader/v_shader.glsl";
  const char* f_shader_path = "../../../asset/shader/f_shader.glsl";

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

GLuint OpenGLManager::LoadVertex() {
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

}  // namespace kplge
