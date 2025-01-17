#pragma once 

#include "Transform.h"
#include "Renderer/MeshRenderer.h"

struct GameObject
{
public:
    Transform transform;
    MeshRenderer* GetMeshRendererPtr();
private:
    MeshRenderer _renderer;
};