#pragma once
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

struct Shader 
{
public:
    void load(std::string vertexPath, std::string fragmentPath);
    void use();
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setMat4(const std::string& name, glm::mat4 value);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec2(const std::string& name, const glm::vec2& value);
    void cleanUp();
private:
    int _id = 0;
};