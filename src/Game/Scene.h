#pragma once

#include "Renderer/SceneRenderer.h"

#include <string>

class Scene
{
private:
    SceneRenderer _sceneRenderer;
public: 
    Scene(std::string sceneName);
    void Load(std::string sceneName);
    void update();
    void cleanUp();
};