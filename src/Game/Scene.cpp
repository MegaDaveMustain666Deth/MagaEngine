#include "Scene.h"

#include <yaml-cpp/yaml.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <glm/vec3.hpp>


void Scene::Load(std::string sceneName)
{
    YAML::Node sceneConf = YAML::LoadFile(std::string("res/Scenes/" + sceneName + ".yaml"));
    int amountVertices = 0, amountIndices = 0, indexVertices = 0, indexIndices = 0,
    amountObjets = sceneConf["Objects"].size();
    std::vector<MeshRenderer*> meshRenderers;

    for(int i = 0; i < amountObjets; i++)
    {
        amountVertices += sceneConf["Objects"]["obj" + std::to_string(i)]["vertices"].size();
        amountIndices += sceneConf["Objects"]["obj" + std::to_string(i)]["indices"].size();

    }

    float *vertices = (float*)malloc(sizeof(float) * amountVertices);
    int *indices = (int*)malloc(sizeof(int) * amountVertices);

    for(int i = 0; i < amountObjets; i++)
    {
        std::string currentObjName = "obj" + std::to_string(i);
        int countElements = sceneConf["Objects"][currentObjName]["vertices"].size();

        for(int j = 0; j < countElements; j++)
        {   
            vertices[j + indexVertices] = sceneConf["Objects"][currentObjName]["vertices"][j].as<float>();
        }

        indexVertices += countElements;
        countElements = sceneConf["Objects"][currentObjName]["indices"].size();

        for(int j = 0; j < countElements; j++)
        {   
            indices[j + indexIndices] = sceneConf["Objects"][currentObjName]["indices"][j].as<int>();
        }

        _gameObjects.emplace_back(GameObject());
        _gameObjects.back().transform.position.x = sceneConf["Objects"]["obj" + std::to_string(i)]["transforms"][0].as<float>();
        _gameObjects.back().transform.position.y = sceneConf["Objects"]["obj" + std::to_string(i)]["transforms"][1].as<float>();
        _gameObjects.back().transform.position.z = sceneConf["Objects"]["obj" + std::to_string(i)]["transforms"][2].as<float>();
        _gameObjects.back().transform.rotation.x = sceneConf["Objects"]["obj" + std::to_string(i)]["transforms"][3].as<float>();
        _gameObjects.back().transform.rotation.y = sceneConf["Objects"]["obj" + std::to_string(i)]["transforms"][4].as<float>();
        _gameObjects.back().transform.rotation.z = sceneConf["Objects"]["obj" + std::to_string(i)]["transforms"][5].as<float>();
        _gameObjects.back().transform.scale.x = sceneConf["Objects"]["obj" + std::to_string(i)]["transforms"][6].as<float>();
        _gameObjects.back().transform.scale.y = sceneConf["Objects"]["obj" + std::to_string(i)]["transforms"][7].as<float>();
        _gameObjects.back().transform.scale.z = sceneConf["Objects"]["obj" + std::to_string(i)]["transforms"][8].as<float>();

        _gameObjects[i].GetMeshRendererPtr()->baseIndex = indexIndices;
        _gameObjects[i].GetMeshRendererPtr()->transform = &_gameObjects[i].transform;
        _gameObjects[i].GetMeshRendererPtr()->amountIndices = countElements;
        _gameObjects[i].GetMeshRendererPtr()->shaderName = sceneConf["Objects"][currentObjName]["shader"].as<std::string>();

        indexIndices += countElements;
        meshRenderers.push_back(_gameObjects[i].GetMeshRendererPtr());
        currentObjName = "obj" + std::to_string(i + 1);
    }

    _sceneRenderer.Setup(vertices, indices, sizeof(float) * amountVertices, sizeof(int) * amountIndices, meshRenderers);
}

void Scene::Update()
{
    _sceneRenderer.Render();
}

Scene::~Scene()
{
    _sceneRenderer.cleanUp();
    _gameObjects.clear();
}