#include "Scene.h"

#include <yaml-cpp/yaml.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

Scene::Scene(std::string sceneName)
{
    Load(sceneName);
}

void Scene::Load(std::string sceneName)
{
    int amountVertices = 0, amountIndices = 0;

    YAML::Node sceneConf = YAML::LoadFile(std::string("res/Scenes/Scene1.yaml"));

    int amountObjets = sceneConf["Objects"].size();

    for(int i = 0; i < amountObjets; i++)
    {
        amountVertices += sceneConf["Objects"]["obj" + std::to_string(i)]["vertices"].size();
        amountIndices += sceneConf["Objects"]["obj" + std::to_string(i)]["indices"].size();
    }

    float *vertices = (float*)malloc(sizeof(float) * amountVertices);
    unsigned int *indices = (unsigned int*)malloc(sizeof(unsigned int) * amountVertices);

    for(int i = 0; i < amountObjets; i++)
    {
        int j;
        int indexVertices;
        int indexIndices;
        int maxCount = sceneConf["Objects"]["obj" + std::to_string(i)]["vertices"].size();
        std::cout << "maxCount" << maxCount << std::endl;

        for(j = 0; j < maxCount; j++)
        {
            vertices[j] = sceneConf["Objects"]["obj" + std::to_string(i)]["vertices"][j].as<float>();
            std::cout << "vertices " << vertices[j] << " obj " << i << std::endl;
        }

        indexVertices += j;

        maxCount = sceneConf["Objects"]["obj" + std::to_string(i)]["indices"].size();
        std::cout << "maxCount" << maxCount << std::endl;

        for(j = 0; j < maxCount; j++)
        {
            indices[j] = sceneConf["Objects"]["obj" + std::to_string(i)]["indices"][j].as<unsigned int>();
            std::cout << "indices " << indices[j] << " obj " << i << std::endl;
        }

        indexIndices += j;
    }

    //     float vertices[] = {
    //      0.5f,  0.5f, 0.0f,  // top right
    //      0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f,  // bottom left
    //     -0.5f,  0.5f, 0.0f   // top left 
    // };
    // unsigned int indices[] = {  // note that we start from 0!
    //     0, 1, 3,  // first Triangle
    //     1, 2, 3   // second Triangle
    // };

    _sceneRenderer.setup(vertices, indices, sizeof(float) * amountVertices, sizeof(unsigned int) * amountIndices);
}

void Scene::update()
{
    _sceneRenderer.render();
}

void Scene::cleanUp()
{
    _sceneRenderer.cleanUp();
}