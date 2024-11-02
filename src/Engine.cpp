#include <Engine.h>
#include <Core.h>
#include <iostream>

void Engine::run()
{
    Core::initalize();

    while(!Core::windowIsOpen())
    {
        Core::beginFrame();
        
        Core::endFrame();
    }

    Core::cleanUp();
}