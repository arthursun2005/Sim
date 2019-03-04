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
    int w = 20;
    int h = 20;
    world->addRect((mouseX * 2.0f - width) * k, (mouseY * 2.0f - height) * -k, w, h, 1.0f);
    //world->addCircle((mouseX * 2.0f - width) * k, (mouseY * 2.0f - height) * -k, 40.0f, 3.0f);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_RELEASE) {
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_RELEASE) {
        if(key == GLFW_KEY_C) {
            printf("%d\n", world->count);
        }
        if(key == GLFW_KEY_W) {
            world->exf *= -1.0f;
        }
        if(key == GLFW_KEY_K) {
            //world->addRect(0.0f, 0.0f, 600, 40, 0.75f);
        }
    }
}

void initialize() {
    initBases();
    
    int w = width * 2 * u;
    int h = height * 2 * u;
    
    printf("sim width: %d\n", w);
    printf("sim height: %d\n", h);
    
    world = new World(w, h, 1024);
    
    world->exf.x = 0.0f;
    world->exf.y = -600.0f;
}

void free() {
    freeBases();
    
    delete world;
}

void draw() {
    world->solve(dt, 1.5f);
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
    
    int w = 200;
    int h = 200;
    
    float s = 0.75f;
    
    world->addRect((w * 3.0f - width) * u * 2.0f, (h * 3.0f - height) * u * -2.0f, w, h, s);
    //world->addRect((width - w * 2.0f) * u * 2.0f, (h * 2.0f - height) * u * -2.0f, w, h, 0.75f);
    //world->addCircle(0.0f, 0.0f, 120.0f, 0.75f);
    
    do {
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
        //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
        
        //world->addRect(0.0f, (70.0f - height) * u * -2.0f, 20, 20, 4.0f);
        
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


