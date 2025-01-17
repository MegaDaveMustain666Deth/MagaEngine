#pragma once

#include <Renderer/SceneRenderer.h>

#include <string>
#include <vector>
#include <Game/GameObject.h>
#include <Game/Camera.h>

class Scene
{
private:
    SceneRenderer _sceneRenderer;
    std::vector<GameObject> _gameObjects;
    Camera *_currentCamera;
    Camera *_cameras;
public: 
    void Load(std::string sceneName);
    void AddCamera(Camera& camera);
    void Update();
    ~Scene();
};