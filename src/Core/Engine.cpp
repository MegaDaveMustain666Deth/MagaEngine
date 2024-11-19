#include "Engine.h"

#include "Core.h"
#include "Game/Scene.h"
#include "Renderer/Shader.h"
#include <iostream>

void Engine::run()
{
    Core::initalize();
    Scene scene("Scene1");
    Shader shader;
    shader.load("res/Shaders/vertex.glsl", "res/Shaders/fragment.glsl");

    while(!Core::windowIsOpen())
    {
        Core::beginFrame();
        shader.use();
        scene.update();
        Core::endFrame();
    }

    scene.cleanUp();
    shader.cleanUp();
    Core::cleanUp();
}