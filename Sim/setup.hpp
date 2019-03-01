//
//  setup.hpp
//  Sim
//
//  Created by Arthur Sun on 2/25/19.
//  Copyright © 2019 Arthur Sun. All rights reserved.
//


#ifndef setup_hpp
#define setup_hpp

#include <iostream>
#include <float.h>
#include <cmath>
#include <vector>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

void initBases();
void freeBases();

void genPoly(float* const vs, int n, float s, float aoffset, int offset);

void print_ftexture_red(int _x, int _y, int _c);
void print_itexture_red(int _x, int _y, int _c);
void print_ftexture_rg(int _x, int _y, int _c);
void print_itexture_rg(int _x, int _y, int _c);

template <class T>
void print_array(T* tp, int _c, int _n, const char* x);

GLuint CreateProgram(const char * _vs[], const char * _fs[], const char* m);
GLuint CreateProgram(const char * _cs[], const char* m);
GLuint LoadProgram(const char * _vs, const char * _fs, const char * _all);
GLuint LoadProgram(const char * _cs, const char * _all);

void checkShader(GLuint x);
void checkProgram(GLuint x);

static GLuint texture_count = 0;

void blit(GLuint target, GLuint x, GLuint y, GLuint w, GLuint h);

inline int nextPowerOfTwo(int x) {
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x + 1;
}

class Shader
{
    
public:
    
    GLuint program;
    
    Shader() {
        program = glCreateProgram();
    }
    
    Shader(const char* cs, const char* all) {
        program = LoadProgram(cs, all);
    }
    
    Shader(const char** vs, const char** fs, const char* m) {
        program = CreateProgram(vs, fs, m);
    }
    
    Shader(const char* vs, const char* fs, const char* all) {
        program = LoadProgram(vs, fs, all);
    }
    
    ~Shader() {
        glDeleteProgram(program);
    }
    
    inline void bind() {
        glUseProgram(program);
    }
    
    inline void uniform1i(const char* n, int i0) const
    {
        glUniform1i(glGetUniformLocation(program, n), i0);
    }
    
    inline void uniform2i(const char* n, int i0, int i1) const
    {
        glUniform2i(glGetUniformLocation(program, n), i0, i1);
    }
    
    inline void uniform2i(const char* n, const glm::ivec2& x) const
    {
        glUniform2i(glGetUniformLocation(program, n), x.x, x.y);
    }
    
    inline void uniform3i(const char* n, int i0, int i1, int i2) const
    {
        glUniform3i(glGetUniformLocation(program, n), i0, i1, i2);
    }
    
    inline void uniform3i(const char* n, const glm::ivec3& x) const
    {
        glUniform3i(glGetUniformLocation(program, n), x.x, x.y, x.z);
    }
    
    inline void uniform4i(const char* n, int i0, int i1, int i2, int i3) const
    {
        glUniform4i(glGetUniformLocation(program, n), i0, i1, i2, i3);
    }
    
    inline void uniform4i(const char* n, const glm::ivec4& x) const
    {
        glUniform4i(glGetUniformLocation(program, n), x.x, x.y, x.z, x.w);
    }
    
    inline void uniform1ui(const char* n, unsigned int i0) const
    {
        glUniform1ui(glGetUniformLocation(program, n), i0);
    }
    
    inline void uniform2ui(const char* n, unsigned int i0, unsigned int i1) const
    {
        glUniform2ui(glGetUniformLocation(program, n), i0, i1);
    }
    
    inline void uniform2ui(const char* n, const glm::uvec2& x) const
    {
        glUniform2ui(glGetUniformLocation(program, n), x.x, x.y);
    }
    
    inline void uniform3ui(const char* n, unsigned int i0, unsigned int i1, unsigned int i2) const
    {
        glUniform3ui(glGetUniformLocation(program, n), i0, i1, i2);
    }
    
    inline void uniform3ui(const char* n, const glm::uvec3& x) const
    {
        glUniform3ui(glGetUniformLocation(program, n), x.x, x.y, x.z);
    }
    
    inline void uniform4ui(const char* n, unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3) const
    {
        glUniform4ui(glGetUniformLocation(program, n), i0, i1, i2, i3);
    }
    
    inline void uniform4ui(const char* n, const glm::uvec4& x) const
    {
        glUniform4ui(glGetUniformLocation(program, n), x.x, x.y, x.z, x.w);
    }
    
    inline void uniform1f(const char* n, float f0) const
    {
        glUniform1f(glGetUniformLocation(program, n), f0);
    }
    
    inline void uniform2f(const char* n, float f0, float f1) const
    {
        glUniform2f(glGetUniformLocation(program, n), f0, f1);
    }
    
    inline void uniform2f(const char* n, const glm::vec2& x) const
    {
        glUniform2f(glGetUniformLocation(program, n), x.x, x.y);
    }
    
    inline void uniform3f(const char* n, float f0, float f1, float f2) const
    {
        glUniform3f(glGetUniformLocation(program, n), f0, f1, f2);
    }
    
    inline void uniform3f(const char* n, const glm::vec3& x) const
    {
        glUniform3f(glGetUniformLocation(program, n), x.x, x.y, x.z);
    }
    
    inline void uniform4f(const char* n, float f0, float f1, float f2, float f3) const
    {
        glUniform4f(glGetUniformLocation(program, n), f0, f1, f2, f3);
    }
    
    inline void uniform4f(const char* n, const glm::vec4& x) const
    {
        glUniform4f(glGetUniformLocation(program, n), x.x, x.y, x.z, x.w);
    }
};

class Texture;

struct FrameBuffer
{
    GLuint fbo;
    
    FrameBuffer() {
        glGenFramebuffers(1, &fbo);
    }
    
    ~FrameBuffer() {
        glDeleteFramebuffers(1, &fbo);
    }
    
    void bind(const Texture* texture, GLenum x) const;
};

class Texture
{
    
public:
    
    GLuint id;
    GLuint texture;
    FrameBuffer* target;
    
    Texture(GLenum mode) {
        id = ++texture_count;
        
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        target = new FrameBuffer();
    }
    
    ~Texture() {
        glDeleteTextures(1, &texture);
        delete target;
    }
    
    void image(GLenum iformat, GLenum format, GLuint x, GLuint y, GLenum type, void* pixels)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, iformat, x, y, 0, format, type, pixels);
        
        setFBO(GL_FRAMEBUFFER);
    }
    
    inline void setFBO(GLenum x) {
        target->bind(this, x);
    }
    
    inline void clear() {
        bind();
        
        glBindFramebuffer(GL_FRAMEBUFFER, target->fbo);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    inline void bind() const
    {
        glActiveTexture(GL_TEXTURE0 + id);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
};

class DoubleTexture {
    
public:
    
    Texture* textures[2];
    
    DoubleTexture(GLenum mode) {
        textures[0] = new Texture(mode);
        textures[1] = new Texture(mode);
    }
    
    ~DoubleTexture()
    {
        delete textures[0];
        delete textures[1];
    }
    
    void image(GLenum iformat, GLenum format, GLuint x, GLuint y, GLenum type, void* pixels) {
        textures[0]->image(iformat, format, x, y, type, pixels);
        textures[1]->image(iformat, format, x, y, type, pixels);
    }
    
    inline const Texture& operator [] (int i) const {
        return *(textures[i]);
    }
    
    inline Texture& operator [] (int i) {
        return *(textures[i]);
    }
    
    inline const Texture& i (int i) const {
        return *(textures[i]);
    }
    
    inline Texture& i (int i) {
        return *(textures[i]);
    }
    
    inline void clear() {
        textures[0]->clear();
        textures[1]->clear();
    }
    
    inline void swap() {
        std::swap(textures[0], textures[1]);
    }
};

inline void clear(GLuint target, float r, float g, float b, float a) {
    glBindFramebuffer(GL_FRAMEBUFFER, target);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

extern GLuint baseVAO;
extern GLuint baseVBO;

#endif /* setup_hpp */
