#include "SceneRenderer.h"

#include <glad/glad.h>
#include <iostream>

void SceneRenderer::setup(float vertices[], unsigned int indices[], int sizeVertices, int sizeIndices)
{
    glGenVertexArrays(1, &_vertexDataVAO);
    glGenBuffers(1, &_vertexDataVBO);
    glGenBuffers(1, &_vertexDataEBO);

    glBindVertexArray(_vertexDataVAO);

    glBindBuffer(GL_ARRAY_BUFFER, _vertexDataVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeVertices, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexDataEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndices, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    
    glBindVertexArray(0); 
}

void SceneRenderer::render()
{
    glBindVertexArray(_vertexDataVAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

void SceneRenderer::cleanUp()
{
    glDeleteVertexArrays(1, &_vertexDataVAO);
    glDeleteBuffers(1, &_vertexDataVBO);
    glDeleteBuffers(1, &_vertexDataEBO);
}