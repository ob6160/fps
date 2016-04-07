#pragma once

// System Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Standard Headers
#include <string>
#include <vector>
#include <cmath>
#include "mesh.hpp"
#include "shader.hpp"


class Level {
     const int levelWidth;
     const int levelHeight;
public:
    Level(int width, int height) : levelWidth(width), levelHeight(height) { };
    ~Level() {
        delete [] map;
    };

    void Construct(Shader *shader);
    int checkCollision(glm::vec3 positionVector);

    Mesh & getMesh() {
        return *levelMesh;
    };

private:
    Mesh *levelMesh;
    int map[10000][10000];
    std::pair<std::vector<GLfloat>, std::vector<GLuint>> GenerateVertices();
};
