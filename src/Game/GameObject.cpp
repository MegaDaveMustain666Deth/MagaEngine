#include "GameObject.h"

#include "Renderer/MeshRenderer.h"

MeshRenderer* GameObject::GetMeshRendererPtr()
{
    return &_renderer;
}