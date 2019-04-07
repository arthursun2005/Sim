//
//  World.hpp
//  Sim
//
//  Created by Arthur Sun on 2/25/19.
//  Copyright © 2019 Arthur Sun. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include "setup.hpp"

class World
{
    
protected:
    
    enum double_textures
    {
        e_velocities = 0,
        e_positions,
        e_grid,
        e_temp,
        e_weights,
        e_pressures,
        e_divergence,
        dtex_end
    };
    
    enum shaders
    {
        e_draw = 0,
        e_partToGrid,
        e_div,
        e_pre,
        e_wvel,
        e_weight,
        e_subtract,
        e_rect,
        e_particle,
        e_step,
        e_force,
        e_extend,
        e_boundry,
        e_show,
        e_gridForce,
        e_copy,
        e_circle,
        e_set,
        sd_end
    };
    
    DoubleTexture* dtex[dtex_end];
    Shader* sd[sd_end];
    
    static const int n_vao = 1;
    static const int n_vbo = 1;
    
    GLuint VAO[n_vao];
    GLuint VBO[n_vbo];
    
    glm::vec2 simSize;
    glm::vec2 gridSize;
    
    int pressure_iterations = 50;
    
    int root;
    glm::vec2 roots;
    
    float solver_record = 0.0f;
    
public:
    
    int count;
    int capacity;
    glm::vec2 exf;
    
    inline void blit(GLuint _target, GLuint vao, int start, int count, const glm::ivec2& _size) {
        glBindFramebuffer(GL_FRAMEBUFFER, _target);
        glBindVertexArray(vao);
        glViewport(0, 0, _size.x, _size.y);
        glDrawArrays(GL_POINTS, start, count);
        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    inline void blit(int x, int i, const glm::ivec2& _size) {
        ::blit(dtex[x]->i(i).target->fbo, 0, 0, _size.x, _size.y);
    }
    
    inline void blit(int x, int i, GLuint vao, int start, int count, const glm::ivec2& _size) {
        blit(dtex[x]->i(i).target->fbo, vao, start, count, _size);
    }
    
    void solve_once();
    
    void weight();
    
    void apply_forces_bound();
    
    void enforceBoundary();
    
    void transfer();
    
    void extend();
    
    void copyToTemp();
    
    void advect_particles();
    
    void toGrid();
    
    void calDivergence();
    
    void solvePressure();
    
    void solveGrid();
    
public:
    
    float dt;
    
    World(int x, int y, int r) : simSize(x, y), gridSize(x + 1.0f, y + 1.0f), count(0), root(r), capacity(r * r), exf(0.0f, 0.0f), roots(r, r)
    {
        dtex[e_positions] = new DoubleTexture(GL_NEAREST);
        dtex[e_positions]->image(GL_RG32F, GL_RG, root, root, GL_FLOAT, 0);
        
        dtex[e_velocities] = new DoubleTexture(GL_NEAREST);
        dtex[e_velocities]->image(GL_RG32F, GL_RG, root, root, GL_FLOAT, 0);
        
        dtex[e_grid] = new DoubleTexture(GL_LINEAR);
        dtex[e_grid]->image(GL_RGBA32F, GL_BGRA, x + 1, y + 1, GL_FLOAT, 0);
        
        dtex[e_temp] = new DoubleTexture(GL_LINEAR);
        dtex[e_temp]->image(GL_RGBA32F, GL_BGRA, x + 1, y + 1, GL_FLOAT, 0);
        
        dtex[e_weights] = new DoubleTexture(GL_LINEAR);
        dtex[e_weights]->image(GL_R32F, GL_RED, x , y , GL_FLOAT, 0);
        
        dtex[e_pressures] = new DoubleTexture(GL_LINEAR);
        dtex[e_pressures]->image(GL_R32F, GL_RED, x, y , GL_FLOAT, 0);
        
        dtex[e_divergence] = new DoubleTexture(GL_LINEAR);
        dtex[e_divergence]->image(GL_R32F, GL_RED, x, y , GL_FLOAT, 0);
        
        sd[e_draw] = new Shader("GLSL/draw.vs", "GLSL/draw.fs", "GLSL/shared.glsl");
        sd[e_partToGrid] = new Shader("GLSL/grid.vs", "GLSL/grid.fs", "GLSL/shared.glsl");
        sd[e_div] = new Shader("GLSL/pass.vs", "GLSL/divergence.fs", "GLSL/shared.glsl");
        sd[e_pre] = new Shader("GLSL/pass.vs", "GLSL/pressure.fs", "GLSL/shared.glsl");
        sd[e_weight] = new Shader("GLSL/texture.vs", "GLSL/weight.fs", "GLSL/shared.glsl");
        sd[e_wvel] = new Shader("GLSL/pass.vs", "GLSL/weightVel.fs", "GLSL/shared.glsl");
        sd[e_subtract] = new Shader("GLSL/pass.vs", "GLSL/subtract.fs", "GLSL/shared.glsl");
        sd[e_rect] = new Shader("GLSL/point.vs", "GLSL/rect.fs", "GLSL/shared.glsl");
        sd[e_particle] = new Shader("GLSL/point.vs", "GLSL/particle.fs", "GLSL/shared.glsl");
        sd[e_force] = new Shader("GLSL/point.vs", "GLSL/force.fs", "GLSL/shared.glsl");
        sd[e_step] = new Shader("GLSL/point.vs", "GLSL/step.fs", "GLSL/shared.glsl");
        sd[e_extend] = new Shader("GLSL/pass.vs", "GLSL/extend.fs", "GLSL/shared.glsl");
        sd[e_boundry] = new Shader("GLSL/pass.vs", "GLSL/boundry.fs", "GLSL/shared.glsl");
        sd[e_show] = new Shader("GLSL/pass.vs", "GLSL/show.fs", "GLSL/shared.glsl");
        sd[e_gridForce] = new Shader("GLSL/pass.vs", "GLSL/gridForce.fs", "GLSL/shared.glsl");
        sd[e_copy] = new Shader("GLSL/pass.vs", "GLSL/copy.fs", "GLSL/shared.glsl");
        sd[e_circle] = new Shader("GLSL/point.vs", "GLSL/circle.fs", "GLSL/shared.glsl");
        sd[e_set] = new Shader("GLSL/point.vs", "GLSL/set.fs", "GLSL/shared.glsl");
        
        for(int i = 0; i < dtex_end; ++i) {
            dtex[i]->clear();
        }
        
        ////////////////////////////
        
        glGenVertexArrays(n_vao, VAO);
        glGenBuffers(n_vbo, VBO);
        
        
        
        std::vector<float> texels(capacity * 2);
        
        for(int py = 0; py < root; ++py) {
            for(int px = 0; px < root; ++px) {
                int i = (px + py * root) * 2;
                texels[i + 0] = (px + 0.5f) / (float)root;
                texels[i + 1] = (py + 0.5f) / (float)root;
            }
        }
        
        
        glBindVertexArray(VAO[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        
        glBufferData(GL_ARRAY_BUFFER, 2 * capacity * sizeof(float), texels.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    ~World() {
        glDeleteVertexArrays(n_vao, VAO);
        glDeleteBuffers(n_vbo, VBO);
        
        for(int i = 0; i < dtex_end; ++i) {
            delete dtex[i];
        }
        
        for(int i = 0; i < sd_end; ++i) {
            delete sd[i];
        }
    }
    
    
    void solve(float its);
    
    
    
    int addCircle(float x, float y, float r, float s);
    
    int addRect(float x, float y, float w, float h, float s);
    
    void addRect(float x, float y, float w, float h, float s, float vx, float vy);
    
    void addCircle(float x, float y, float r, float s, float vx, float vy);
    
    
    
    
    void render(GLuint target, int x, int y, int w, int h);
};

#endif /* World_hpp */
