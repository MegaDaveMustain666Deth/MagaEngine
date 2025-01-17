#pragma once 

#include <Renderer/Shader.h>
#include <Game/Transform.h>

struct MeshRenderer 
{
public: 
    int baseIndex;
    float amountIndices;
    Shader *shader;
    Transform *transform;
    std::string shaderName;
};  