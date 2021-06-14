//
//  SimpleShader.hpp
//  OpenGL_tut_Udemy
//
//  Created by Simona Bilkova on 14/6/21.
//

#ifndef SimpleShader_hpp
#define SimpleShader_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class SimpleShader
{
public:
    SimpleShader();
    ~SimpleShader();
    
    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    
    std::string ReadFile(const char* filePath);
    
    void CreateFromString(const char* vertexCode, const char* fragmentCode);
    void CreateFromFiles(const char* vertexPath, const char* fragmentPath);
    void UseShader();
    void ClearShader();

    
private:
    GLuint shaderID, uniformModel, uniformProjection;
    
    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
    
};
#endif /* SimpleShader_hpp */
