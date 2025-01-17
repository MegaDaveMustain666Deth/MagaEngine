#pragma once

#include <Tools/Vector.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Core/Core.h>
#include <Game/Transform.h>

class Camera
{
public:
    Camera(float fov, float far, float near, glm::vec3 position, glm::vec3 rotation)
    {
        _fov = fov; 
        _far = far; 
        _near = near;
        _transform.position = position;
        _transform.rotation = rotation;
    }

    glm::mat4 GetView()
    {
        return glm::lookAt(_transform.position, _transform.position + vector::forward, vector::up);
    }

    glm::mat4 GetProjection()
    {
        return glm::perspective(glm::radians(_fov), (float)Core::getWindowedWidth() / Core::getWindowedHeight(), _near, _far);
    }

private:
    float _fov = 90;
    float _far = 10;
    float _near = 0;
    Transform _transform;
};