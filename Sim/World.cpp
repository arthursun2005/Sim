//
//  World.cpp
//  Sim
//
//  Created by Arthur Sun on 2/25/19.
//  Copyright © 2019 Arthur Sun. All rights reserved.
//

#include "World.hpp"

void World::solve_once(float dt) {
    // transfering particle velocities to MAC grid
    toGrid();
    
    extend();
    
    copyToTemp();
    
    apply_forces_bound(dt);
    
    // weighting each cell, 0 means air, >0 means liquid
    weight();
    
    // calculating the divergence
    calDivergence();
    
    // solve pressure from that
    for(int n = 0; n < pressure_iterations; ++n)
        solvePressure();
    
    // solving the grid
    solveGrid();
    
    transfer();
    
    advect_particles(dt);
}

void World::toGrid() {
    dtex[e_positions]->i(1).bind();
    dtex[e_velocities]->i(1).bind();
    
    dtex[e_grid]->i(1).clear();
    
    sd[e_partToGrid]->bind();
    sd[e_partToGrid]->uniform1i("P", dtex[e_positions]->i(1).id);
    sd[e_partToGrid]->uniform1i("V", dtex[e_velocities]->i(1).id);
    sd[e_partToGrid]->uniform2f("size", simSize);
    
    dtex[e_grid]->i(1).bind();
    
    glEnable(GL_BLEND);
    blit(e_grid, 1, VAO[1], 0, count * 2, gridSize);
    glDisable(GL_BLEND);
    
    
    sd[e_wvel]->bind();
    sd[e_wvel]->uniform2f("invSize", 1.0f/gridSize);
    sd[e_wvel]->uniform1i("V", dtex[e_grid]->i(1).id);
    
    dtex[e_grid]->i(0).bind();
    blit(e_grid, 0, gridSize);
    
    dtex[e_grid]->swap();
    
    reset_texture_count;
}

void World::extend() {
    dtex[e_grid]->i(1).bind();
    
    sd[e_extend]->bind();
    sd[e_extend]->uniform2f("invSize", 1.0f/gridSize);
    sd[e_extend]->uniform1i("V", dtex[e_grid]->i(1).id);
    
    dtex[e_grid]->i(0).bind();
    blit(e_grid, 0, gridSize);
    
    dtex[e_grid]->swap();
    
    reset_texture_count;
}

void World::weight() {
    dtex[e_positions]->i(1).bind();
    
    dtex[e_weights]->i(1).clear();
    
    sd[e_weight]->bind();
    sd[e_weight]->uniform1i("T", dtex[e_positions]->i(1).id);
    sd[e_weight]->uniform2f("scl", 1.0f/simSize);
    sd[e_weight]->uniform1f("size", 1.0f);
    
    dtex[e_weights]->i(1).bind();
    glEnable(GL_BLEND);
    blit(e_weights, 1, VAO[0], 0, count, simSize);
    glDisable(GL_BLEND);
    
    reset_texture_count;
}

void World::calDivergence() {
    dtex[e_grid]->i(1).bind();
    dtex[e_weights]->i(1).bind();
    
    sd[e_div]->bind();
    sd[e_div]->uniform2f("invSize", 1.0f/gridSize);
    sd[e_div]->uniform1i("V", dtex[e_grid]->i(1).id);
    sd[e_div]->uniform1i("M", dtex[e_weights]->i(1).id);
    
    dtex[e_divergence]->i(1).bind();
    blit(e_divergence, 1, simSize);
    
    reset_texture_count;
}

void World::solvePressure() {
    
    
    dtex[e_divergence]->i(1).bind();
    dtex[e_weights]->i(1).bind();
    dtex[e_pressures]->i(1).bind();
    
    
    sd[e_pre]->bind();
    sd[e_pre]->uniform2f("invSize", 1.0f/simSize);
    sd[e_pre]->uniform1i("D", dtex[e_divergence]->i(1).id);
    sd[e_pre]->uniform1i("M", dtex[e_weights]->i(1).id);

    sd[e_pre]->uniform1i("P", dtex[e_pressures]->i(1).id);
    
    dtex[e_pressures]->i(0).bind();
    blit(e_pressures, 0, simSize);
    
    dtex[e_pressures]->swap();
    
    reset_texture_count;
    
}

void World::solveGrid() {
    dtex[e_pressures]->i(1).bind();
    dtex[e_grid]->i(1).bind();
    dtex[e_weights]->i(1).bind();
    
    sd[e_subtract]->bind();
    sd[e_subtract]->uniform2f("invGrid", 1.0f/gridSize);
    sd[e_subtract]->uniform2f("invSize", 1.0f/simSize);
    sd[e_subtract]->uniform1i("U", dtex[e_pressures]->i(1).id);
    sd[e_subtract]->uniform1i("V", dtex[e_grid]->i(1).id);
    sd[e_subtract]->uniform1i("W", dtex[e_weights]->i(1).id);
    
    dtex[e_grid]->i(0).bind();
    blit(e_grid, 0, gridSize);
    
    dtex[e_grid]->swap();
    
    reset_texture_count;
}

void World::transfer() {
    dtex[e_temp]->i(1).bind();
    dtex[e_positions]->i(1).bind();
    dtex[e_grid]->i(1).bind();
    dtex[e_velocities]->i(1).bind();
    
    sd[e_particle]->bind();
    sd[e_particle]->uniform2f("invSize", 1.0f/roots);
    sd[e_particle]->uniform2f("size", simSize);
    sd[e_particle]->uniform1i("T", dtex[e_temp]->i(1).id);
    sd[e_particle]->uniform1i("P", dtex[e_positions]->i(1).id);
    sd[e_particle]->uniform1i("G", dtex[e_grid]->i(1).id);
    sd[e_particle]->uniform1i("V", dtex[e_velocities]->i(1).id);
    
    dtex[e_velocities]->i(0).bind();
    blit(e_velocities, 0, VAO[0], 0, count, roots);
    
    dtex[e_velocities]->swap();
    
    reset_texture_count;
}

void World::enforceBoundary() {
    sd[e_boundry]->bind();
    sd[e_boundry]->uniform2f("size", gridSize);
    sd[e_boundry]->uniform1i("V", dtex[e_grid]->i(1).id);
    
    dtex[e_grid]->i(0).bind();
    blit(e_grid, 0, gridSize);
    
    dtex[e_grid]->swap();
}

void World::apply_forces_bound(float dt) {
    dtex[e_grid]->i(1).bind();
    
    sd[e_gridForce]->bind();
    sd[e_gridForce]->uniform1f("dt", dt);
    sd[e_gridForce]->uniform2f("exf", exf);
    sd[e_gridForce]->uniform2f("size", gridSize);
    sd[e_gridForce]->uniform1i("V", dtex[e_grid]->i(1).id);
    
    dtex[e_grid]->i(0).bind();
    blit(e_grid, 0, gridSize);
    
    dtex[e_grid]->swap();
    
    reset_texture_count;
}

void World::advect_particles(float dt) {
    dtex[e_grid]->i(1).bind();
    dtex[e_positions]->i(1).bind();
    dtex[e_velocities]->i(1).bind();
    
    sd[e_step]->bind();
    sd[e_step]->uniform2f("invSize", 1.0f/roots);
    sd[e_step]->uniform2f("size", simSize);
    sd[e_step]->uniform1f("dt", dt);
    sd[e_step]->uniform1i("V", dtex[e_velocities]->i(1).id);
    sd[e_step]->uniform1i("P", dtex[e_positions]->i(1).id);
    sd[e_step]->uniform1i("G", dtex[e_grid]->i(1).id);
    sd[e_step]->uniform1f("seed", time(0));
    
    dtex[e_positions]->i(0).bind();
    blit(e_positions, 0, VAO[0], 0, count, roots);
    
    dtex[e_positions]->swap();
    
    reset_texture_count;
}






void World::addRect(float x, float y, int w, int h, float s) {
    int i = w * h;
    
    assert(count + i <= capacity);
    
    sd[e_rect]->bind();
    sd[e_rect]->uniform1f("sp", s);
    sd[e_rect]->uniform2f("pos", x, y);
    sd[e_rect]->uniform1i("hx", w);
    sd[e_rect]->uniform1i("hy", h);
    sd[e_rect]->uniform1i("count", count);
    sd[e_rect]->uniform1i("root", root);
    
    dtex[e_positions]->i(1).bind();
    blit(e_positions, 1, VAO[0], count, i, roots);
    
    count += i;
    
    reset_texture_count;
}

void World::addCircle(float x, float y, float r, float s) {
    int i = (int)(M_PI * r * r / (s * s));
    
    assert(count + i <= capacity);
    
    sd[e_circle]->bind();
    sd[e_circle]->uniform1f("radius", r);
    sd[e_circle]->uniform2f("pos", x, y);
    
    dtex[e_positions]->i(1).bind();
    blit(e_positions, 1, VAO[0], count, i, roots);
    
    count += i;
    
    reset_texture_count;
}

void World::copyToTemp() {
    dtex[e_grid]->i(1).bind();
    
    sd[e_copy]->bind();
    sd[e_copy]->uniform1i("T", dtex[e_grid]->i(1).id);
    
    dtex[e_temp]->i(1).bind();
    blit(e_temp, 1, gridSize);
    
    reset_texture_count;
}


void World::render(GLuint _target, int x, int y, int w, int h) {
    bool gg = false;
    
    if(!gg) {
        dtex[e_positions]->i(1).bind();
        
        sd[e_draw]->bind();
        sd[e_draw]->uniform1i("T", dtex[e_positions]->i(1).id);
        sd[e_draw]->uniform2f("scl", 1.0f/simSize);
        sd[e_draw]->uniform1f("size", 2.0f);
        
        //glEnable(GL_BLEND);
        
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _target);
        glBindVertexArray(VAO[0]);
        glViewport(x, y, w, h);
        glDrawArrays(GL_POINTS, 0, count);
        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        //glDisable(GL_BLEND);
        
        reset_texture_count;
    }else{
     
    
    
        sd[e_show]->bind();
        sd[e_show]->uniform1i("M", dtex[e_weights]->i(1).id);
        sd[e_show]->uniform1i("V", dtex[e_grid]->i(1).id);
        sd[e_show]->uniform2f("invSize", 1.0f/(float)w, 1.0f/(float)h);
        sd[e_show]->uniform2f("gridSize", simSize);
        sd[e_show]->uniform2f("size", w, h);
        
        ::blit(_target, x, y, w, h);
    
        
    }
      
}
