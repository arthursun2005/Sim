//
//  main.cpp
//  Sim
//
//  Created by Arthur Sun on 2/25/19.
//  Copyright © 2019 Arthur Sun. All rights reserved.
//

#include "World.hpp"

GLFWwindow *window;
const GLFWvidmode* mode;

double mouseX = 0.0f, mouseY = 0.0f;
double pmouseX = mouseX, pmouseY = mouseY;
float width, height;
float dt = 0.016f;
float windowScl = 0.75f;
float u = 0.1f;

int framesPerSecond = 0;
float lastSecondTime = glfwGetTime();

World* world;

void addFromMouse() {
    float k = 2.0f * u;
    int w = 60;
    int h = 60;
    world->addRect((mouseX * 2.0f - width) * k, (mouseY * 2.0f - height) * -k, w, h, 0.61f);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_RELEASE) {
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_RELEASE) {
        if(key ==  GLFW_KEY_C) {
            printf("%d\n", world->count);
        }
    }
}

void initialize() {
    initBases();
    
    world = new World(width * 2 * u, height * 2 * u, 2048);
}

void free() {
    freeBases();
    
    delete world;
}

void draw() {
    world->solve_once(dt);
    world->render(0, 0, 0, width * 2, height * 2);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
}

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
    if(!glfwInit()) return 1;
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);
    
    width = (float)mode->width * windowScl;
    height = (float)mode->height * windowScl;
    
    window = glfwCreateWindow(width, height, "Sim", NULL, NULL);
    
    glfwMakeContextCurrent(window);
    glewInit();
    
    const unsigned char* t = glGetString(GL_VERSION);
    
    printf("%s\n", t);
    
    initialize();
    
    glfwSetMouseButtonCallback(window, mouseCallback);
    
    GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
    
    glfwSetCursor(window, cursor);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetScrollCallback(window, scrollCallback);
    
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);
    
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    
    do {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwGetCursorPos(window, &mouseX, &mouseY);
        
        float currentTime = glfwGetTime();
        bool press = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        
        ++framesPerSecond;
        if(currentTime - lastSecondTime >= 1.0f) {
            printf("%f ms/frame \n", 1000.0f * (currentTime - lastSecondTime)/(float)framesPerSecond);
            framesPerSecond = 0;
            lastSecondTime = currentTime;
        }
        
        if(press == GLFW_PRESS) {
            addFromMouse();
        }
        
        draw();
        
        glfwPollEvents();
        glfwSwapBuffers(window);
        
        pmouseX = mouseX;
        pmouseY = mouseY;
    } while (glfwWindowShouldClose(window) == GL_FALSE && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
    free();
    glfwDestroyCursor(cursor);
    glfwTerminate();
    return 0;
}


