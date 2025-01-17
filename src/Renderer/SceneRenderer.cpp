#include "SceneRenderer.h"

#include <glad/glad.h>
#include <iostream>
#include <Renderer/MeshRenderer.h>
#include <yaml-cpp/yaml.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Core/Core.h>

void SceneRenderer::Setup(float vertices[], int indices[], int sizeVertices, int sizeIndices, std::vector<MeshRenderer*> &meshRenderers)
{
    YAML::Node shaderConf = YAML::LoadFile("res/Configs/Shaders.yaml");
    _amountShaders = shaderConf.size();
    _meshRenderers = meshRenderers;
    int amountMeshs = _meshRenderers.size();

    for(int i = 0; i < _amountShaders; i++)
    {
        std::pair<std::string, Shader*> pair = std::make_pair(shaderConf[i]["name"].as<std::string>(),
         new Shader(shaderConf[i]["vertex"].as<std::string>(), shaderConf[i]["fragment"].as<std::string>()));
        _shaders.insert(pair);
    }

    for(int i = 0; i < amountMeshs; i++)
    {
        _meshRenderers[i]->shader = _shaders[_meshRenderers[i]->shaderName];
    }

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

void SceneRenderer::Render()
{
    glBindVertexArray(_vertexDataVAO);
    int amountMeshs = _meshRenderers.size();

    for(int i = 0; i < amountMeshs; i++)
    {
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)Core::getWindowedWidth() / (float)Core::getWindowedHeight(), 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        _meshRenderers[i]->shader->setMat4("projection", projection);
        _meshRenderers[i]->shader->setMat4("view", view);
        _meshRenderers[i]->shader->setMat4("model", _meshRenderers[i]->transform->GetModel());
        _meshRenderers[i]->shader->use();
        glDrawElementsBaseVertex(GL_TRIANGLES, _meshRenderers[i]->amountIndices, GL_UNSIGNED_INT, 0, _meshRenderers[i]->baseIndex);
    }
}

void SceneRenderer::cleanUp()
{
    _meshRenderers.clear();
    _shaders.clear();
    glDeleteVertexArrays(1, &_vertexDataVAO);
    glDeleteBuffers(1, &_vertexDataVBO);
    glDeleteBuffers(1, &_vertexDataEBO);
}