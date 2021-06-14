#include <stdio.h>
#include <string.h>
#include <cmath>
#include <math.h>
#include <vector>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TrangleWindow.hpp"
#include "mesh.hpp"
#include "SimpleShader.hpp"

TriangleWindow* mainWindow;
std::vector<Mesh*> meshList;
std::vector<SimpleShader*> shaderList;

float currSize = 0.4f;

// Vertex shader
static const char* vShaderPath = "Shaders/shader1.vert";

// Fragment shader
static const char* fShaderPath = "Shaders/shader1.frag";

void createObjects()
{
    
    unsigned int indices[] = {
        0, 1, 2,
        1, 3, 2,
        0, 2, 3,
        3, 1, 0
    };
    
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
         0.0f, -1.0f, 1.0f
    };
    
    Mesh *mesh1 = new Mesh();
    mesh1->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(mesh1);
    
    Mesh *mesh2 = new Mesh();
    mesh2->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(mesh2);
    
}

void CreateShaders()
{
    SimpleShader* shader1 = new SimpleShader();
    shader1->CreateFromFiles(vShaderPath, fShaderPath);
    shaderList.push_back(shader1);
}


int main()
{
    mainWindow = new TriangleWindow();
    mainWindow->init();
    
    createObjects();
    CreateShaders();
    
    GLuint uniformProjection = 0, uniformModel = 0;
    glm::mat4 projection = glm::perspective(45.0f, mainWindow->getBufferWidth() / mainWindow->getBufferheight(), 0.1f, 100.0f);
    
    while ( !mainWindow->getShouldClose() )
    {
        glfwPollEvents();
        glClearColor( 0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shaderList[0]->UseShader();
        uniformModel = shaderList[0]->GetModelLocation();
        uniformProjection = shaderList[0]->GetProjectionLocation();
        
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.7f, -2.5f));
        model = glm:: scale(model, glm::vec3(currSize, currSize, 1.0f));
        
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.7f, -2.5f));
        model = glm:: scale(model, glm::vec3(currSize, currSize, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshList[1]->RenderMesh();

        glUseProgram(0);
        
        mainWindow->swapBuffers();

    }
    
    mainWindow->~TriangleWindow();
    return SUCCESS;
}
