#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;

// Vertex shader
static const char* vShader = "                      \n\
#version 330                                        \n\
layout (location = 0) in vec3 pos;              \n\
                                                    \n\
void main() {                                       \n\
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);   \n\
}";

// Fragment shader
static const char* fShader = "                      \n\
#version 330                                        \n\
out vec4 colour;                                    \n\
                                                    \n\
void main() {                                       \n\
    colour = vec4(0.0, 0.0, 0.3, 1.0);   \n\
}";

void createTriangle()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f
    };
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);
    
    const GLchar* theCode[1];
    theCode[0] = shaderCode;
    
    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);
    
    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);
    
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    
    if (!result) {
        glGetProgramInfoLog(theShader, sizeof(eLog), nullptr, eLog);
        printf("Error compiling the %d shader: '%s' \n ",shaderType, eLog);
        return;
    }
    
    glAttachShader(theProgram, theShader);
}

void compileShaders() {
    shader = glCreateProgram();
    
    if ( !shader )
    {
        printf("Error creating shader program");
        return;
    }
    
    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);
    
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        printf("Error linking program: '%s' \n ", eLog);
        return;
    }
    
    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        printf("Error validating program: '%s' \n ", eLog);
        return;
    }
    
    
    
}


int main()
{
    if ( !glfwInit() )
    {
        printf("GLFW initialisation failed!");
        glfwTerminate();
        return 1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    
    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Tutorial", nullptr, nullptr);
    if ( !mainWindow )
    {
        printf( "Failed to initalise GLFW window" );
        glfwTerminate();
        return 1;
    }
    
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    
    glfwMakeContextCurrent(mainWindow);
    glewExperimental = GL_TRUE;
    
    if ( glewInit() != GLEW_OK )
    {
        printf( "Failed to initalise GLEW\n" );
        glfwTerminate();
        return 1;
    }
    
    glViewport(0, 0, bufferWidth, bufferHeight);
    
    createTriangle();
    compileShaders();
    
    while ( !glfwWindowShouldClose(mainWindow) )
    {
        glfwPollEvents();
        glClearColor( 0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shader);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        glUseProgram(0);
        
        glfwSwapBuffers(mainWindow);
    }
    
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    return 1;
}
