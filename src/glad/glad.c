/*
 * GLAD Implementation - OpenGL 3.3 Core Profile Loader
 * Loads OpenGL function pointers at runtime via WGL/EGL
 */
#define GLAD_GL_IMPLEMENTATION
#include <stddef.h>
#include "glad.h"

#ifdef __cplusplus
extern "C" {
#endif

// GLAD API pointer definitions
#define GLAD_API_PTR

// Function pointer storage
PFNGLCLEARPROC glad_glClear = NULL;
PFNGLCLEARCOLORPROC glad_glClearColor = NULL;
PFNGLVIEWPORTPROC glad_glViewport = NULL;
PFNGLENABLEPROC glad_glEnable = NULL;
PFNGLDISABLEPROC glad_glDisable = NULL;
PFNGLBLENDFUNCPROC glad_glBlendFunc = NULL;
PFNGLCULLFACEPROC glad_glCullFace = NULL;
PFNGLDEPTHFUNCPROC glad_glDepthFunc = NULL;
PFNGLDEPTHMASKPROC glad_glDepthMask = NULL;
PFNGLPOLYGONMODEPROC glad_glPolygonMode = NULL;
PFNGLPIXELSTOREIPROC glad_glPixelStorei = NULL;

PFNGLCREATESHADERPROC glad_glCreateShader = NULL;
PFNGLSHADERSOURCEPROC glad_glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glad_glCompileShader = NULL;
PFNGLDELETESHADERPROC glad_glDeleteShader = NULL;
PFNGLGETSHADERIVPROC glad_glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog = NULL;

PFNGLCREATEPROGRAMPROC glad_glCreateProgram = NULL;
PFNGLATTACHSHADERPROC glad_glAttachShader = NULL;
PFNGLLINKPROGRAMPROC glad_glLinkProgram = NULL;
PFNGLDELETEPROGRAMPROC glad_glDeleteProgram = NULL;
PFNGLUSEPROGRAMPROC glad_glUseProgram = NULL;
PFNGLGETPROGRAMIVPROC glad_glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog = NULL;
PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation = NULL;
PFNGLUNIFORM1FPROC glad_glUniform1f = NULL;
PFNGLUNIFORM1IPROC glad_glUniform1i = NULL;
PFNGLUNIFORM3FPROC glad_glUniform3f = NULL;
PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv = NULL;

PFNGLGENBUFFERSPROC glad_glGenBuffers = NULL;
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers = NULL;
PFNGLBINDBUFFERPROC glad_glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glad_glBufferData = NULL;

PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays = NULL;
PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer = NULL;

PFNGLGENTEXTURESPROC glad_glGenTextures = NULL;
PFNGLDELETETEXTURESPROC glad_glDeleteTextures = NULL;
PFNGLBINDTEXTUREPROC glad_glBindTexture = NULL;
PFNGLTEXIMAGE2DPROC glad_glTexImage2D = NULL;
PFNGLTEXPARAMETERIPROC glad_glTexParameteri = NULL;
PFNGLACTIVETEXTUREPROC glad_glActiveTexture = NULL;

PFNGLDRAWARRAYSPROC glad_glDrawArrays = NULL;
PFNGLDRAWELEMENTSPROC glad_glDrawElements = NULL;

PFNGLGETSTRINGPROC glad_glGetString = NULL;
PFNGLGETERRORPROC glad_glGetError = NULL;

// Helper to load a function pointer
static void* glad_get_proc(const char* name, GLADloadproc load) {
    void* proc = load(name);
    return proc;
}

int gladLoadGLLoader(GLADloadproc load) {
    if (load == NULL) return 0;

    // Core 1.0
    glad_glClear = (PFNGLCLEARPROC)glad_get_proc("glClear", load);
    glad_glClearColor = (PFNGLCLEARCOLORPROC)glad_get_proc("glClearColor", load);
    glad_glViewport = (PFNGLVIEWPORTPROC)glad_get_proc("glViewport", load);
    glad_glEnable = (PFNGLENABLEPROC)glad_get_proc("glEnable", load);
    glad_glDisable = (PFNGLDISABLEPROC)glad_get_proc("glDisable", load);
    glad_glBlendFunc = (PFNGLBLENDFUNCPROC)glad_get_proc("glBlendFunc", load);
    glad_glCullFace = (PFNGLCULLFACEPROC)glad_get_proc("glCullFace", load);
    glad_glDepthFunc = (PFNGLDEPTHFUNCPROC)glad_get_proc("glDepthFunc", load);
    glad_glDepthMask = (PFNGLDEPTHMASKPROC)glad_get_proc("glDepthMask", load);
    glad_glPolygonMode = (PFNGLPOLYGONMODEPROC)glad_get_proc("glPolygonMode", load);
    glad_glPixelStorei = (PFNGLPIXELSTOREIPROC)glad_get_proc("glPixelStorei", load);

    glad_glGetString = (PFNGLGETSTRINGPROC)glad_get_proc("glGetString", load);
    glad_glGetError = (PFNGLGETERRORPROC)glad_get_proc("glGetError", load);

    glad_glDrawArrays = (PFNGLDRAWARRAYSPROC)glad_get_proc("glDrawArrays", load);
    glad_glDrawElements = (PFNGLDRAWELEMENTSPROC)glad_get_proc("glDrawElements", load);

    // Textures (1.1+)
    glad_glGenTextures = (PFNGLGENTEXTURESPROC)glad_get_proc("glGenTextures", load);
    glad_glDeleteTextures = (PFNGLDELETETEXTURESPROC)glad_get_proc("glDeleteTextures", load);
    glad_glBindTexture = (PFNGLBINDTEXTUREPROC)glad_get_proc("glBindTexture", load);
    glad_glTexImage2D = (PFNGLTEXIMAGE2DPROC)glad_get_proc("glTexImage2D", load);
    glad_glTexParameteri = (PFNGLTEXPARAMETERIPROC)glad_get_proc("glTexParameteri", load);
    glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC)glad_get_proc("glActiveTexture", load);

    // Shaders (2.0+)
    glad_glCreateShader = (PFNGLCREATESHADERPROC)glad_get_proc("glCreateShader", load);
    glad_glShaderSource = (PFNGLSHADERSOURCEPROC)glad_get_proc("glShaderSource", load);
    glad_glCompileShader = (PFNGLCOMPILESHADERPROC)glad_get_proc("glCompileShader", load);
    glad_glDeleteShader = (PFNGLDELETESHADERPROC)glad_get_proc("glDeleteShader", load);
    glad_glGetShaderiv = (PFNGLGETSHADERIVPROC)glad_get_proc("glGetShaderiv", load);
    glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glad_get_proc("glGetShaderInfoLog", load);

    glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC)glad_get_proc("glCreateProgram", load);
    glad_glAttachShader = (PFNGLATTACHSHADERPROC)glad_get_proc("glAttachShader", load);
    glad_glLinkProgram = (PFNGLLINKPROGRAMPROC)glad_get_proc("glLinkProgram", load);
    glad_glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glad_get_proc("glDeleteProgram", load);
    glad_glUseProgram = (PFNGLUSEPROGRAMPROC)glad_get_proc("glUseProgram", load);
    glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)glad_get_proc("glGetProgramiv", load);
    glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)glad_get_proc("glGetProgramInfoLog", load);
    glad_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)glad_get_proc("glGetUniformLocation", load);
    glad_glUniform1f = (PFNGLUNIFORM1FPROC)glad_get_proc("glUniform1f", load);
    glad_glUniform1i = (PFNGLUNIFORM1IPROC)glad_get_proc("glUniform1i", load);
    glad_glUniform3f = (PFNGLUNIFORM3FPROC)glad_get_proc("glUniform3f", load);
    glad_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)glad_get_proc("glUniformMatrix4fv", load);

    // VAO/VBO (3.0+ Core)
    glad_glGenBuffers = (PFNGLGENBUFFERSPROC)glad_get_proc("glGenBuffers", load);
    glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glad_get_proc("glDeleteBuffers", load);
    glad_glBindBuffer = (PFNGLBINDBUFFERPROC)glad_get_proc("glBindBuffer", load);
    glad_glBufferData = (PFNGLBUFFERDATAPROC)glad_get_proc("glBufferData", load);

    glad_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glad_get_proc("glGenVertexArrays", load);
    glad_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glad_get_proc("glDeleteVertexArrays", load);
    glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glad_get_proc("glBindVertexArray", load);
    glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glad_get_proc("glEnableVertexAttribArray", load);
    glad_glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)glad_get_proc("glDisableVertexAttribArray", load);
    glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)glad_get_proc("glVertexAttribPointer", load);

    // Verify essential functions loaded
    if (!glad_glClear || !glad_glCreateShader || !glad_glGenVertexArrays) {
        return 0;
    }

    return 1;
}

#ifdef __cplusplus
}
#endif