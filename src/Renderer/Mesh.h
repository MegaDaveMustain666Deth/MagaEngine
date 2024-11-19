#pragma once 

#include "Types.h"

struct Mesh 
{
    public:
        //vector<Vertex>       vertices;

        //Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        ///void Draw(Shader &shader);
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
};  