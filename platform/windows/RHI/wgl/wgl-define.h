#pragma once
#include <Windows.h>
#include <gl/gl.h>

typedef GLvoid(APIENTRY* PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
typedef GLvoid(APIENTRY* PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
typedef GLvoid(APIENTRY* PFNGLBINDVERTEXARRAYPROC)(GLuint array);
typedef GLvoid(APIENTRY* PFNGLBUFFERDATAPROC)(
    GLenum target, ptrdiff_t size, const GLvoid* data, GLenum usage);
typedef GLvoid(APIENTRY* PFNGLCOMPILESHADERPROC)(GLuint shader);
typedef GLuint(APIENTRY* PFNGLCREATEPROGRAMPROC)(GLvoid);
typedef GLuint(APIENTRY* PFNGLCREATESHADERPROC)(GLenum type);
typedef GLvoid(APIENTRY* PFNGLDELETEBUFFERSPROC)(
    GLsizei n, const GLuint* buffers);
typedef GLvoid(APIENTRY* PFNGLDELETEPROGRAMPROC)(GLuint program);
typedef GLvoid(APIENTRY* PFNGLDELETESHADERPROC)(GLuint shader);
typedef GLvoid(APIENTRY* PFNGLDELETEVERTEXARRAYSPROC)(
    GLsizei n, const GLuint* arrays);
typedef GLvoid(APIENTRY* PFNGLDETACHSHADERPROC)(GLuint program, GLuint shader);
typedef GLvoid(APIENTRY* PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef GLvoid(APIENTRY* PFNGLGENBUFFERSPROC)(GLsizei n, GLuint* buffers);
typedef GLvoid(APIENTRY* PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint* arrays);
typedef GLint(APIENTRY* PFNGLGETATTRIBLOCATIONPROC)(
    GLuint program, const char* name);
typedef GLvoid(APIENTRY* PFNGLGETPROGRAMINFOLOGPROC)(
    GLuint program, GLsizei bufSize, GLsizei* length, char* infoLog);
typedef GLvoid(APIENTRY* PFNGLGETPROGRAMIVPROC)(
    GLuint program, GLenum pname, GLint* params);
typedef GLvoid(APIENTRY* PFNGLGETSHADERINFOLOGPROC)(
    GLuint shader, GLsizei bufSize, GLsizei* length, char* infoLog);
typedef GLvoid(APIENTRY* PFNGLGETSHADERIVPROC)(
    GLuint shader, GLenum pname, GLint* params);
typedef GLvoid(APIENTRY* PFNGLLINKPROGRAMPROC)(GLuint program);
typedef GLvoid(APIENTRY* PFNGLSHADERSOURCEPROC)(
    GLuint shader, GLsizei count, const char** string, const GLint* length);
typedef GLvoid(APIENTRY* PFNGLUSEPROGRAMPROC)(GLuint program);
typedef GLvoid(APIENTRY* PFNGLVERTEXATTRIBPOINTERPROC)(
    GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
    const GLvoid* pointer);
typedef GLvoid(APIENTRY* PFNGLBINDATTRIBLOCATIONPROC)(
    GLuint program, GLuint index, const char* name);
typedef GLint(APIENTRY* PFNGLGETUNIFORMLOCATIONPROC)(
    GLuint program, const char* name);
typedef GLvoid(APIENTRY* PFNGLUNIFORMMATRIX4FVPROC)(
    GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef GLvoid(APIENTRY* PFNGLACTIVETEXTUREPROC)(GLenum texture);
typedef GLvoid(APIENTRY* PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
typedef GLvoid(APIENTRY* PFNGLGENERATEMIPMAPPROC)(GLenum target);
typedef GLvoid(APIENTRY* PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
typedef GLvoid(APIENTRY* PFNGLUNIFORM3FVPROC)(
    GLint location, GLsizei count, const GLfloat* value);
typedef GLvoid(APIENTRY* PFNGLUNIFORM4FVPROC)(
    GLint location, GLsizei count, const GLfloat* value);