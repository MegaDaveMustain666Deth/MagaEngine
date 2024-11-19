#include <glad/glad.h>

struct SceneRenderer
{
public:
    void setup(float vertices[], unsigned int indices[], int sizeVertices, int sizeIndices);
    void render();
    void cleanUp();

private:
    unsigned int _vertexDataVAO = 0, _vertexDataVBO = 0, _vertexDataEBO = 0;
    int _amountVertices;
};