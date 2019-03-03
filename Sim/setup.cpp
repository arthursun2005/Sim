//
//  setup.cpp
//  Sim
//
//  Created by Arthur Sun on 2/25/19.
//  Copyright © 2019 Arthur Sun. All rights reserved.
//

#include "setup.hpp"
#include <fstream>
#include <sstream>

GLuint baseVAO;
GLuint baseVBO;

const GLfloat baseQuad[] = {
    -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f
};

GLuint CreateProgram(const char * _vs[], const char * _fs[], const char* m) {
    GLuint programID = glCreateProgram();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vs, 1, _vs, nullptr);
    glShaderSource(fs, 1, _fs, nullptr);
    glCompileShader(vs);
    glCompileShader(fs);
    checkShader(vs);
    checkShader(fs);
    glAttachShader(programID, vs);
    glAttachShader(programID, fs);
    glLinkProgram(programID);
    checkProgram(programID);
    glDetachShader(programID, vs);
    glDetachShader(programID, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    printf("compiled %s \n", m);
    
    return programID;
}

GLuint CreateProgram(const char * _cs[], const char* m) {
    GLuint programID = glCreateProgram();
    GLuint cs = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(cs, 1, _cs, nullptr);
    glCompileShader(cs);
    checkShader(cs);
    glAttachShader(programID, cs);
    glLinkProgram(programID);
    glDetachShader(programID, cs);
    glDeleteShader(cs);
    
    checkProgram(programID);
    printf("compiled %s \n", m);
    
    return programID;
}

GLuint LoadProgram(const char * _vs, const char * _fs, const char * _all) {
    std::ifstream vs(_vs, std::ios::in);
    std::ifstream fs(_fs, std::ios::in);
    std::ifstream all(_all, std::ios::in);
    
    std::stringstream vstr, fstr, astr;
    
    bool failed = false;
    
    if(vs.is_open()) {
        vstr << vs.rdbuf();
        vs.close();
    }else{
        printf("%s can't be opened \n", _vs);
        failed = true;
    }
    
    if(fs.is_open()) {
        fstr << fs.rdbuf();
        fs.close();
    }else{
        printf("%s can't be opened \n", _fs);
        failed = true;
    }
    
    if(_all && all.is_open()) {
        astr << all.rdbuf();
        all.close();
    }else if(_all) {
        printf("%s can't be opened \n", _all);
        failed = true;
    }
    
    if(failed)
        return 0;
    
    std::string __v = astr.str();
    std::string __f(__v);
    std::string __vs = vstr.str();
    std::string __fs = fstr.str();
    
    __v.append(__vs);
    __f.append(__fs);
    
    const char* fvs = __v.c_str();
    const char* ffs = __f.c_str();
    
    return CreateProgram(&fvs, &ffs, _fs);
}

GLuint LoadProgram(const char * _cs, const char * _all) {
    std::ifstream cs(_cs, std::ios::in);
    std::ifstream all(_all, std::ios::in);
    
    std::stringstream cstr, astr;
    
    bool failed = false;
    
    if(cs.is_open()) {
        cstr << cs.rdbuf();
        cs.close();
    }else{
        printf("%s can't be opened \n", _cs);
        failed = true;
    }
    
    if(_all && all.is_open()) {
        astr << all.rdbuf();
        all.close();
    }else if(_all) {
        printf("%s can't be opened \n", _all);
        failed = true;
    }
    
    if(failed)
        return 0;
    
    std::string __c = astr.str();
    std::string __cs = cstr.str();
    
    __c.append(__cs);
    
    const char* fcs = __c.c_str();
    
    return CreateProgram(&fcs, _cs);
}

void checkShader(GLuint x) {
    int status;
    glGetShaderiv(x, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) {
        int length;
        glGetShaderiv(x, GL_INFO_LOG_LENGTH, &length);
        GLchar log[length];
        glGetShaderInfoLog(x, length, nullptr, log);
        printf("%s \n", log);
    }
}

void checkProgram(GLuint x) {
    int status;
    glGetProgramiv(x, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) {
        int length;
        glGetProgramiv(x, GL_INFO_LOG_LENGTH, &length);
        GLchar log[length];
        glGetProgramInfoLog(x, length, nullptr, log);
        printf("%s \n", log);
    }
}

void FrameBuffer::bind(const Texture* texture, GLenum x) const
{
    glBindFramebuffer(x, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->texture, 0);
    assert(glCheckFramebufferStatus(x) == GL_FRAMEBUFFER_COMPLETE);
    glBindFramebuffer(x, 0);
}

void initBases() {
    glGenVertexArrays(1, &baseVAO);
    glGenBuffers(1, &baseVBO);
    
    glBindVertexArray(baseVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, baseVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(baseQuad), baseQuad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
}

void freeBases() {
    glDeleteVertexArrays(1, &baseVAO);
    glDeleteBuffers(1, &baseVBO);
}

void blit(GLuint target, GLuint x, GLuint y, GLuint w, GLuint h) {
    glBindFramebuffer(GL_FRAMEBUFFER, target);
    glBindVertexArray(baseVAO);
    glViewport(x, y, w, h);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void genPoly(float* const vs, int n, float s, float aoffset, int offset) {
    float a = 2.0f * M_PI / n;
    float k_c = cosf(a);
    float k_s = sinf(a);
    float x = cosf(aoffset) * s;
    float y = sinf(aoffset) * s;
    for(uint32_t i = 0; i < n; ++i) {
        vs[(i << 1) + offset] = x;
        vs[(i << 1) + 1 + offset] = y;
        x = x * k_c - y * k_s;
        y = vs[(i << 1) + offset] * k_s + y * k_c;
    }
}

template <class T>
void print_array(T* tp, int _c, int _n, const char* x) {
    for(uint32_t i = 0; i < _c; ++i) {
        for(int k = 0; k < _n; ++k) {
            printf(x, tp[i * _n + k]);
            if(k < _n - 1) printf(", ");
        }
        printf("\n");
    }
    printf("\n");
}


void print_ftexture_red(int _x, int _y, int _c) {
    float tp[_x * _y];
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_FLOAT, tp);
    print_array(tp, _c, 1, "%f");
}

void print_itexture_red(int _x, int _y, int _c) {
    float tp[_x * _y];
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RED_INTEGER, GL_INT, tp);
    print_array(tp, _c, 1, "%d");
}

void print_ftexture_rg(int _x, int _y, int _c) {
    float tp[_x * _y * 2];
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RG, GL_FLOAT, tp);
    print_array(tp, _c, 2, "%f");
}

void print_itexture_rg(int _x, int _y, int _c) {
    int tp[_x * _y * 2];
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RG_INTEGER, GL_INT, tp);
    print_array(tp, _c, 2, "%d");
}
