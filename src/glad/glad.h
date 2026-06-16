/*
 * GLAD - OpenGL Loader Generator (Hand-generated for GL 3.3 Core)
 * This is a minimal GLAD implementation for OpenGL 3.3 Core Profile
 * Based on the glad2 API style
 */
#ifndef GLAD_GL_H_
// Prevent system GL/gl.h from being included (GLFW tries to include it)
#define __gl_h_
#define __GL_H__
#define _GL_H
#define __gltypes_h_
#define __glext_h_
#define GLAD_GL_H_

// GLAD API export/import macros
// In glad.c, define GLAD_GL_IMPLEMENTATION before including glad.h
// This makes the variable declarations become definitions.
#ifdef GLAD_GL_IMPLEMENTATION
  #define GLAD_VAR
#else
  #define GLAD_VAR extern
#endif

#ifndef GLAD_API_PTR
  #define GLAD_API_PTR
#endif

#ifdef __cplusplus
extern "C" {
#endif

// GL types
typedef void GLvoid;
typedef unsigned int GLenum;
typedef int GLint;
typedef int GLsizei;
typedef unsigned int GLbitfield;
typedef double GLdouble;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef unsigned char GLboolean;
typedef unsigned char GLubyte;
typedef signed char GLbyte;
typedef short GLshort;
typedef unsigned short GLushort;
typedef long GLintptr;
typedef long GLsizeiptr;
typedef char GLchar;
typedef long GLsync;

// GL constants (3.3 Core subset)
#define GL_FALSE                          0
#define GL_TRUE                           1
#define GL_NONE                           0
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_FRONT_AND_BACK                 0x0408
#define GL_CW                             0x0900
#define GL_CCW                            0x0901
#define GL_POLYGON_MODE                   0x0B40
#define GL_CULL_FACE                      0x0B44
#define GL_DEPTH_TEST                     0x0B71
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_STENCIL_TEST                   0x0B90
#define GL_VIEWPORT                       0x0BA2
#define GL_BLEND                          0x0BE2
#define GL_SCISSOR_BOX                    0x0C10
#define GL_SCISSOR_TEST                   0x0C11
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_ALIGNMENT                 0x0D05
#define GL_MAX_TEXTURE_SIZE               0x0D33
#define GL_TEXTURE_2D                     0x0DE1
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_DOUBLE                         0x140A
#define GL_RGBA                           0x1908
#define GL_RGB                            0x1907
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_LINEAR                         0x2601
#define GL_NEAREST                        0x2600
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_REPEAT                         0x2901
#define GL_COLOR_ATTACHMENT0              0x8CE0
#define GL_DEPTH_ATTACHMENT               0x8D00
#define GL_FRAMEBUFFER                    0x8D40
#define GL_RENDERBUFFER                   0x8D41
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_STATIC_DRAW                    0x88E4
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_STREAM_DRAW                    0x88E0
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_TEXTURE0                       0x84C0
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02

// GL function pointer type
typedef void* (*GLADloadproc)(const char *name);

// GL function declarations
typedef void (GLAD_API_PTR *PFNGLCLEARPROC)(GLbitfield);
typedef void (GLAD_API_PTR *PFNGLCLEARCOLORPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GLAD_API_PTR *PFNGLVIEWPORTPROC)(GLint, GLint, GLsizei, GLsizei);
typedef void (GLAD_API_PTR *PFNGLENABLEPROC)(GLenum);
typedef void (GLAD_API_PTR *PFNGLDISABLEPROC)(GLenum);
typedef void (GLAD_API_PTR *PFNGLBLENDFUNCPROC)(GLenum, GLenum, GLenum, GLenum);
typedef void (GLAD_API_PTR *PFNGLCULLFACEPROC)(GLenum);
typedef void (GLAD_API_PTR *PFNGLDEPTHFUNCPROC)(GLenum);
typedef void (GLAD_API_PTR *PFNGLDEPTHMASKPROC)(GLboolean);
typedef void (GLAD_API_PTR *PFNGLPOLYGONMODEPROC)(GLenum, GLenum);
typedef void (GLAD_API_PTR *PFNGLPIXELSTOREIPROC)(GLenum, GLint);

typedef GLuint (GLAD_API_PTR *PFNGLCREATESHADERPROC)(GLenum);
typedef void (GLAD_API_PTR *PFNGLSHADERSOURCEPROC)(GLuint, GLsizei, const GLchar* const*, const GLint*);
typedef void (GLAD_API_PTR *PFNGLCOMPILESHADERPROC)(GLuint);
typedef void (GLAD_API_PTR *PFNGLDELETESHADERPROC)(GLuint);
typedef void (GLAD_API_PTR *PFNGLGETSHADERIVPROC)(GLuint, GLenum, GLint*);
typedef void (GLAD_API_PTR *PFNGLGETSHADERINFOLOGPROC)(GLuint, GLsizei, GLsizei*, GLchar*);

typedef GLuint (GLAD_API_PTR *PFNGLCREATEPROGRAMPROC)(void);
typedef void (GLAD_API_PTR *PFNGLATTACHSHADERPROC)(GLuint, GLuint);
typedef void (GLAD_API_PTR *PFNGLLINKPROGRAMPROC)(GLuint);
typedef void (GLAD_API_PTR *PFNGLDELETEPROGRAMPROC)(GLuint);
typedef void (GLAD_API_PTR *PFNGLUSEPROGRAMPROC)(GLuint);
typedef void (GLAD_API_PTR *PFNGLGETPROGRAMIVPROC)(GLuint, GLenum, GLint*);
typedef void (GLAD_API_PTR *PFNGLGETPROGRAMINFOLOGPROC)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef GLint (GLAD_API_PTR *PFNGLGETUNIFORMLOCATIONPROC)(GLuint, const GLchar*);
typedef void (GLAD_API_PTR *PFNGLUNIFORM1FPROC)(GLint, GLfloat);
typedef void (GLAD_API_PTR *PFNGLUNIFORM1IPROC)(GLint, GLint);
typedef void (GLAD_API_PTR *PFNGLUNIFORM3FPROC)(GLint, GLfloat, GLfloat, GLfloat);
typedef void (GLAD_API_PTR *PFNGLUNIFORMMATRIX4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);

typedef void (GLAD_API_PTR *PFNGLGENBUFFERSPROC)(GLsizei, GLuint*);
typedef void (GLAD_API_PTR *PFNGLDELETEBUFFERSPROC)(GLsizei, const GLuint*);
typedef void (GLAD_API_PTR *PFNGLBINDBUFFERPROC)(GLenum, GLuint);
typedef void (GLAD_API_PTR *PFNGLBUFFERDATAPROC)(GLenum, GLsizeiptr, const void*, GLenum);

typedef void (GLAD_API_PTR *PFNGLGENVERTEXARRAYSPROC)(GLsizei, GLuint*);
typedef void (GLAD_API_PTR *PFNGLDELETEVERTEXARRAYSPROC)(GLsizei, const GLuint*);
typedef void (GLAD_API_PTR *PFNGLBINDVERTEXARRAYPROC)(GLuint);
typedef void (GLAD_API_PTR *PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint);
typedef void (GLAD_API_PTR *PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint);
typedef void (GLAD_API_PTR *PFNGLVERTEXATTRIBPOINTERPROC)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);

typedef void (GLAD_API_PTR *PFNGLGENTEXTURESPROC)(GLsizei, GLuint*);
typedef void (GLAD_API_PTR *PFNGLDELETETEXTURESPROC)(GLsizei, const GLuint*);
typedef void (GLAD_API_PTR *PFNGLBINDTEXTUREPROC)(GLenum, GLuint);
typedef void (GLAD_API_PTR *PFNGLTEXIMAGE2DPROC)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
typedef void (GLAD_API_PTR *PFNGLTEXPARAMETERIPROC)(GLenum, GLenum, GLint);
typedef void (GLAD_API_PTR *PFNGLACTIVETEXTUREPROC)(GLenum);

typedef void (GLAD_API_PTR *PFNGLDRAWARRAYSPROC)(GLenum, GLint, GLsizei);
typedef void (GLAD_API_PTR *PFNGLDRAWELEMENTSPROC)(GLenum, GLsizei, GLenum, const void*);

typedef void (GLAD_API_PTR *PFNGLREADBUFFERPROC)(GLenum);
typedef const GLubyte* (GLAD_API_PTR *PFNGLGETSTRINGPROC)(GLenum);
typedef GLenum (GLAD_API_PTR *PFNGLGETERRORPROC)(void);
typedef void (GLAD_API_PTR *PFNGLFINISHPROC)(void);
typedef void (GLAD_API_PTR *PFNGLFLUSHPROC)(void);

// GLAD API function pointers (extern)
GLAD_VAR PFNGLCLEARPROC glad_glClear;
GLAD_VAR PFNGLCLEARCOLORPROC glad_glClearColor;
GLAD_VAR PFNGLVIEWPORTPROC glad_glViewport;
GLAD_VAR PFNGLENABLEPROC glad_glEnable;
GLAD_VAR PFNGLDISABLEPROC glad_glDisable;
GLAD_VAR PFNGLBLENDFUNCPROC glad_glBlendFunc;
GLAD_VAR PFNGLCULLFACEPROC glad_glCullFace;
GLAD_VAR PFNGLDEPTHFUNCPROC glad_glDepthFunc;
GLAD_VAR PFNGLDEPTHMASKPROC glad_glDepthMask;
GLAD_VAR PFNGLPOLYGONMODEPROC glad_glPolygonMode;
GLAD_VAR PFNGLPIXELSTOREIPROC glad_glPixelStorei;

GLAD_VAR PFNGLCREATESHADERPROC glad_glCreateShader;
GLAD_VAR PFNGLSHADERSOURCEPROC glad_glShaderSource;
GLAD_VAR PFNGLCOMPILESHADERPROC glad_glCompileShader;
GLAD_VAR PFNGLDELETESHADERPROC glad_glDeleteShader;
GLAD_VAR PFNGLGETSHADERIVPROC glad_glGetShaderiv;
GLAD_VAR PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog;

GLAD_VAR PFNGLCREATEPROGRAMPROC glad_glCreateProgram;
GLAD_VAR PFNGLATTACHSHADERPROC glad_glAttachShader;
GLAD_VAR PFNGLLINKPROGRAMPROC glad_glLinkProgram;
GLAD_VAR PFNGLDELETEPROGRAMPROC glad_glDeleteProgram;
GLAD_VAR PFNGLUSEPROGRAMPROC glad_glUseProgram;
GLAD_VAR PFNGLGETPROGRAMIVPROC glad_glGetProgramiv;
GLAD_VAR PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog;
GLAD_VAR PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation;
GLAD_VAR PFNGLUNIFORM1FPROC glad_glUniform1f;
GLAD_VAR PFNGLUNIFORM1IPROC glad_glUniform1i;
GLAD_VAR PFNGLUNIFORM3FPROC glad_glUniform3f;
GLAD_VAR PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv;

GLAD_VAR PFNGLGENBUFFERSPROC glad_glGenBuffers;
GLAD_VAR PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;
GLAD_VAR PFNGLBINDBUFFERPROC glad_glBindBuffer;
GLAD_VAR PFNGLBUFFERDATAPROC glad_glBufferData;

GLAD_VAR PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays;
GLAD_VAR PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays;
GLAD_VAR PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray;
GLAD_VAR PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;
GLAD_VAR PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray;
GLAD_VAR PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;

GLAD_VAR PFNGLGENTEXTURESPROC glad_glGenTextures;
GLAD_VAR PFNGLDELETETEXTURESPROC glad_glDeleteTextures;
GLAD_VAR PFNGLBINDTEXTUREPROC glad_glBindTexture;
GLAD_VAR PFNGLTEXIMAGE2DPROC glad_glTexImage2D;
GLAD_VAR PFNGLTEXPARAMETERIPROC glad_glTexParameteri;
GLAD_VAR PFNGLACTIVETEXTUREPROC glad_glActiveTexture;

GLAD_VAR PFNGLDRAWARRAYSPROC glad_glDrawArrays;
GLAD_VAR PFNGLDRAWELEMENTSPROC glad_glDrawElements;

GLAD_VAR PFNGLGETSTRINGPROC glad_glGetString;
GLAD_VAR PFNGLGETERRORPROC glad_glGetError;

// Macro aliases (so code can use glXxx directly)
#define glClear                  glad_glClear
#define glClearColor             glad_glClearColor
#define glViewport               glad_glViewport
#define glEnable                 glad_glEnable
#define glDisable                glad_glDisable
#define glBlendFunc              glad_glBlendFunc
#define glCullFace               glad_glCullFace
#define glDepthFunc              glad_glDepthFunc
#define glDepthMask              glad_glDepthMask
#define glPolygonMode            glad_glPolygonMode
#define glPixelStorei            glad_glPixelStorei

#define glCreateShader           glad_glCreateShader
#define glShaderSource           glad_glShaderSource
#define glCompileShader          glad_glCompileShader
#define glDeleteShader           glad_glDeleteShader
#define glGetShaderiv            glad_glGetShaderiv
#define glGetShaderInfoLog       glad_glGetShaderInfoLog

#define glCreateProgram          glad_glCreateProgram
#define glAttachShader           glad_glAttachShader
#define glLinkProgram            glad_glLinkProgram
#define glDeleteProgram          glad_glDeleteProgram
#define glUseProgram             glad_glUseProgram
#define glGetProgramiv           glad_glGetProgramiv
#define glGetProgramInfoLog      glad_glGetProgramInfoLog
#define glGetUniformLocation     glad_glGetUniformLocation
#define glUniform1f              glad_glUniform1f
#define glUniform1i              glad_glUniform1i
#define glUniform3f              glad_glUniform3f
#define glUniformMatrix4fv       glad_glUniformMatrix4fv

#define glGenBuffers             glad_glGenBuffers
#define glDeleteBuffers          glad_glDeleteBuffers
#define glBindBuffer             glad_glBindBuffer
#define glBufferData             glad_glBufferData

#define glGenVertexArrays        glad_glGenVertexArrays
#define glDeleteVertexArrays     glad_glDeleteVertexArrays
#define glBindVertexArray        glad_glBindVertexArray
#define glEnableVertexAttribArray  glad_glEnableVertexAttribArray
#define glDisableVertexAttribArray glad_glDisableVertexAttribArray
#define glVertexAttribPointer    glad_glVertexAttribPointer

#define glGenTextures            glad_glGenTextures
#define glDeleteTextures         glad_glDeleteTextures
#define glBindTexture            glad_glBindTexture
#define glTexImage2D             glad_glTexImage2D
#define glTexParameteri          glad_glTexParameteri
#define glActiveTexture          glad_glActiveTexture

#define glDrawArrays             glad_glDrawArrays
#define glDrawElements           glad_glDrawElements

#define glGetString              glad_glGetString
#define glGetError               glad_glGetError

// GLAD init function
int gladLoadGLLoader(GLADloadproc load);

#ifdef __cplusplus
}
#endif

#endif /* GLAD_GL_H_ */