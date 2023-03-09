#include "opengl-manager.h"
#include <gl/gl.h>
#include <vcruntime.h>

#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

#include "asset-loader.h"
#include "private/matrix.h"
#include "scene-manager.h"

namespace kplge {
erroc OpenGLManager::Initialize() {
  glEnable(GL_DEPTH_TEST);

  InitializeShaders("v_shader.glsl", "f_shader.glsl");
  InitializeBuffers();
  return KPL_NO_ERR;
}
erroc OpenGLManager::Finalize() { return KPL_NO_ERR; }
erroc OpenGLManager::Tick() {
  Clear();
  if (!Draw()) return GFX_ERR_RUNT;
  return KPL_NO_ERR;
}

bool OpenGLManager::Draw() {
  RenderBuffers();
  glFlush();
  return 1;
}

bool OpenGLManager::Clear() {
  glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
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
  auto& root = p_sceneManager_->GetSceneRenderRoot();
  LoadNode(root);
  return 1;
}

bool OpenGLManager::RenderBuffers() {
  for (auto dbc : drawBatchContexts_) {
    glUseProgram(shaderProgram_);
    Matrix4X4f view{{1, 0, 0, 2}, {0, 1, 0, 3}, {0, 0, 0, -4}, {0, 0, 0, 1}};
    SetPerBatchShaderParameters("ModelMatrix", dbc.transform);
    glDrawArrays(dbc.mode, 0, dbc.count);
    // glDrawElements(dbc.mode, dbc.count, dbc.indices_type, 0x00);
  }

  return 1;
}

bool OpenGLManager::SetPerBatchShaderParameters(
    const char* paramName, const Matrix4X4f& param) {
  GLuint location;
  location = glGetUniformLocation(shaderProgram_, paramName);
  if (location == -1) return false;
  glUniformMatrix4fv(location, 1, false, param);
  return 1;
}

bool OpenGLManager::LoadNode(SceneNode& node) {
  for (auto& meshNode : node.GetMeshNodes()) {
    LoadMeshNode(meshNode);
  }
  return 1;
}

bool OpenGLManager::LoadMeshNode(SceneMeshNode& node) {
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  auto mesh = node.GetMesh();
  GLenum indices_type;
  for (auto indexArray : mesh->GetIndexArraies()) {
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, indexArray.GetData().size(),
        indexArray.GetData().data(), GL_STATIC_DRAW);

    switch (indexArray.dataType_) {
      case IndexDataType::I8:
        indices_type = GL_UNSIGNED_BYTE;
      case IndexDataType::I16:
        indices_type = GL_UNSIGNED_SHORT;
      case IndexDataType::I32:
        indices_type = GL_UNSIGNED_INT;
        break;
    }

    buffers_.push_back(ebo);
  }

  GLuint count;
  for (auto vertexArray : mesh->GetVertexArraies()) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
        GL_ARRAY_BUFFER, vertexArray.GetData().size(),
        vertexArray.GetData().data(), GL_STATIC_DRAW);

    buffers_.push_back(vbo);

    count = vertexArray.count_;

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
    GLenum type;
    switch (vertexArray.dataType_) {
      case VertexDataType::VEC2F:
        size = 2;
        type = GL_FLOAT;
        break;
      case VertexDataType::VEC3F:
        size = 3;
        type = GL_FLOAT;
        break;
      case VertexDataType::VEC4F:
        size = 4;
        type = GL_FLOAT;
        break;
      case VertexDataType::VEC2D:
        size = 2;
        type = GL_DOUBLE;
        break;
      case VertexDataType::VEC3D:
        size = 3;
        type = GL_DOUBLE;
        break;
      case VertexDataType::VEC4D:
        size = 4;
        type = GL_DOUBLE;
        break;
        break;
    }

    glEnableVertexAttribArray(vaa);
    glVertexAttribPointer(
        vaa, size, type, vertexArray.normalized_ ? GL_TRUE : GL_FALSE, 0,
        (void*)0);
  }

  GLenum mode;
  switch (mesh->GetPrimitiveMode()) {
    case PrimitiveMode::POINTS:
      mode = GL_POINTS;
      break;
    case PrimitiveMode::LINES:
      mode = GL_LINES;
      break;
    case PrimitiveMode::LINE_LOOP:
      mode = GL_LINE_LOOP;
      break;
    case PrimitiveMode::LINE_STRIP:
      mode = GL_LINE_STRIP;
      break;
    case PrimitiveMode::TRIANGLES:
      mode = GL_TRIANGLES;
      break;
    case PrimitiveMode::TRIANGLE_STRIP:
      mode = GL_TRIANGLE_STRIP;
      break;
    case PrimitiveMode::TRIANGLE_FAN:
      mode = GL_TRIANGLE_FAN;
      break;
  }

  DrawBatchContext dbc;
  dbc.vao = vao;
  dbc.mode = mode;
  dbc.count = count;
  dbc.indices_type = indices_type;
  dbc.transform = node.GetTransformMatrix();
  drawBatchContexts_.emplace_back(std::move(dbc));
  return 1;
}
}  // namespace kplge
