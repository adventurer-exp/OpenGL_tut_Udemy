//
//  TrangleWindow.cpp
//  OpenGL_tut_Udemy
//
//  Created by Simona Bilkova on 15/6/21.
//

#include "TrangleWindow.hpp"

TriangleWindow::TriangleWindow()
{
    width = 800;
    height = 600;
}

TriangleWindow::TriangleWindow(GLint width, GLint height)
{
    this->width = width;
    this->height = height;
}

TriangleWindow::~TriangleWindow()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

int TriangleWindow::init()
{
    if ( !glfwInit() )
    {
        printf("GLFW initialisation failed!");
        glfwTerminate();
        return FAIL;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    
    mainWindow = glfwCreateWindow(width, height, "OpenGL Tutorial", nullptr, nullptr);
    if ( !mainWindow )
    {
        printf( "Failed to initalise GLFW window" );
        glfwTerminate();
        return FAIL;
    }
    
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    
    glfwMakeContextCurrent(mainWindow);
    glewExperimental = GL_TRUE;
    
    if ( glewInit() != GLEW_OK )
    {
        printf( "Failed to initalise GLEW\n" );
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }
    
    glEnable(GL_DEPTH_TEST);
    
    glViewport(0, 0, bufferWidth, bufferHeight);
    
    return SUCCESS;
}
