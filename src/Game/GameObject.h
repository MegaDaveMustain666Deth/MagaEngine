#pragma once 
#include "Transform.h"

struct GameObject
{
public:
    GameObject(int beginVertex, float amountVertices);
private:
    int _beginVertex;
    float _amountVertices;
    Transform _transform;
};