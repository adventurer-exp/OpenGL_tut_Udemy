//
//  SimpleShader.cpp
//  OpenGL_tut_Udemy
//
//  Created by Simona Bilkova on 14/6/21.
//

#include "SimpleShader.hpp"

SimpleShader::SimpleShader()
{
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
}

GLuint SimpleShader::GetModelLocation()
{
    return uniformModel;
}

GLuint SimpleShader::GetProjectionLocation()
{
    return uniformProjection;
}

std::string SimpleShader::ReadFile(const char *filePath)
{
    std::string fileContent;
    std::ifstream fileStream(filePath, std::ios::in);
    
    if (!fileStream.is_open())
    {
        printf("Failed to open the file. Is your path correct? %s", filePath);
        return "";
    }
    
    std::string line = "";
    
    while (!fileStream.eof() ) {
        std::getline(fileStream, line);
        fileContent.append(line + "\n");
    }
    fileStream.close();
    
    return fileContent;
}

void SimpleShader::CreateFromFiles(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexString = ReadFile(vertexPath);
    std::string fragmentString = ReadFile(fragmentPath);
    
    const char* vertexCode = vertexString.c_str();
    const char* fragCode = fragmentString.c_str();
    
    CompileShader(vertexCode, fragCode);
}

void SimpleShader::AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType)
{
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
        //return;
    }
    
    glAttachShader(theProgram, theShader);
}

void SimpleShader::CompileShader(const char *vertexCode, const char *fragmentCode)
{
    shaderID = glCreateProgram();
    
    if ( !shaderID )
    {
        printf("Error creating shader program");
        //return;
    }
    
    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);
    
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    
    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        printf("Error linking program: '%s' \n ", eLog);
        //return;
    }
    
    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        printf("Error validating program: '%s' \n ", eLog);
        //return;
    }
    
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformModel = glGetUniformLocation(shaderID, "model");
}

void SimpleShader::CreateFromString(const char *vertexCode, const char *fragmentCode)
{
    CompileShader(vertexCode, fragmentCode);
}

void SimpleShader::UseShader()
{
    glUseProgram(shaderID);
}

void SimpleShader::ClearShader()
{
    if (shaderID != 0)
    {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
    
    uniformModel = 0;
    uniformProjection = 0;
}

SimpleShader::~SimpleShader()
{
    ClearShader();
}
