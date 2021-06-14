//
//  mesh.hpp
//  OpenGL_tut_Udemy
//
//  Created by Simona Bilkova on 14/6/21.
//

#ifndef mesh_hpp
#define mesh_hpp

#include <stdio.h>
#include <GL/glew.h>

class Mesh
{
public:
    Mesh();
    ~Mesh();
    
    void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void RenderMesh();
    void ClearMesh();
    
private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
    
};


#endif /* mesh_hpp */
