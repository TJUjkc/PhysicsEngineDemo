#pragma once
#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>

static GLuint g_shaderProgram = 0;

inline GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        OutputDebugStringA("Shader compile error: ");
        OutputDebugStringA(infoLog);
        OutputDebugStringA("\n");
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

inline GLuint createShaderProgram(
    const char* vertexSource, const char* fragmentSource)
{
    GLuint vert = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint frag = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    if (!vert || !frag) {
        if (vert) glDeleteShader(vert);
        if (frag) glDeleteShader(frag);
        return 0;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        OutputDebugStringA("Program link error: ");
        OutputDebugStringA(infoLog);
        OutputDebugStringA("\n");
        glDeleteProgram(program);
        program = 0;
    }

    glDeleteShader(vert);
    glDeleteShader(frag);

    return program;
}

inline void useShader(GLuint program) {
    glUseProgram(program);
}

inline void releaseShader() {
    if (g_shaderProgram) {
        glDeleteProgram(g_shaderProgram);
        g_shaderProgram = 0;
    }
}
