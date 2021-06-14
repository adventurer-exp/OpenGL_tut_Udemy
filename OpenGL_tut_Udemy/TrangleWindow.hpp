//
//  TrangleWindow.hpp
//  OpenGL_tut_Udemy
//
//  Created by Simona Bilkova on 15/6/21.
//

#ifndef TrangleWindow_hpp
#define TrangleWindow_hpp

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define SUCCESS 0
#define FAIL 1


class TriangleWindow
{
public:
    TriangleWindow();
    TriangleWindow(GLint windowWidth, GLint windowHeight);
    ~TriangleWindow();
    
    int init();
    
    GLfloat getBufferWidth() { return bufferWidth; };
    GLfloat getBufferheight() { return bufferHeight; };
    
    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); };
    
    void swapBuffers() { glfwSwapBuffers(mainWindow); };
    
private:
    GLFWwindow *mainWindow;
    
    GLint width, height, bufferWidth, bufferHeight;
    
};
#endif /* TrangleWindow_hpp */
