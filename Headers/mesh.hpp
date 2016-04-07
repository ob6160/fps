#pragma once

// System Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Standard Headers
#include <string>
#include <vector>
#include "texture.hpp"

class Mesh
{
public:
    Mesh();
    Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices, GLuint shaderProgram);
    ~Mesh();

    void render();

    void Translate(glm::vec3 addVector);

    void Identity(glm::mat4 setTo);

    void Rotate(glm::vec3 rotVector, GLfloat angle);

    void setVertices(std::vector<GLfloat> vertices, std::vector<GLuint> indices);

    void setup();

    void setTexture(Texture *texture) {
        this->texture = texture;
    };

    Texture & getTexture() {
        return *this->texture;
    };

    void bind();
protected:

private:
    GLuint vertexArrayObject, vertexBuffer, elementBuffer, shaderProgram;

    //TODO: Support more than one texture per mesh
    Texture* texture;

    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    glm::mat4 transform;
};
