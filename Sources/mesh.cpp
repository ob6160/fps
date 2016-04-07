#include "mesh.hpp"

using namespace std;

Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices, GLuint shaderProgram)
{
    this->shaderProgram = shaderProgram;
    setVertices(vertices, indices);
}

Mesh::Mesh(){
    setup();
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &elementBuffer);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::setup(){
    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &elementBuffer);
}

void Mesh::setVertices(std::vector<GLfloat> vertices, std::vector<GLuint> indices) {
    this->vertices = vertices;
    this->indices = indices;
}

void Mesh::bind() {
    glBindVertexArray(vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat), this->vertices.data(), GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (void*)(6*sizeof(GLfloat)));


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_STATIC_DRAW);



    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}
void Mesh::render(){

    this->getTexture().bind();


    glBindVertexArray(vertexArrayObject);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(transform));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, NULL);
}

void Mesh::Identity(glm::mat4 setTo) {

    transform = setTo;
}

void Mesh::Translate(glm::vec3 addVector){
    transform = glm::translate(transform, addVector);
}

void Mesh::Rotate(glm::vec3 rotVector, GLfloat angle){
    transform = glm::rotate(transform, glm::radians(angle), rotVector);
}



