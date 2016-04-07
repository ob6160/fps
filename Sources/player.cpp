#include <GLFW/glfw3.h>
#include "player.hpp"


void Player::Update(double delta, Level *level, bool *keys) {
    glm::vec3 oldposition = camera->Position;
    glm::vec3 moveBy = HandleInput(delta, keys);

    int collide;

    glm::vec3 tempPosition;

    tempPosition = oldposition;
    tempPosition.x += moveBy.x;

    collide = level->checkCollision(tempPosition);

    if(!collide) {
        camera->Position.x = tempPosition.x;
    }

    tempPosition = oldposition;
    tempPosition.z += moveBy.z;
    collide = level->checkCollision(tempPosition);

    if(!collide) {
        camera->Position.z = tempPosition.z;
    };
};

glm::vec3 Player::HandleInput(double delta, bool *keys) {
    glm::vec3 moveBy;

    if(keys[GLFW_KEY_W])
    moveBy += camera->Front * (GLfloat)(this->speed * delta);
    if(keys[GLFW_KEY_S])
    moveBy -= camera->Front * (GLfloat)(this->speed * delta);
    if(keys[GLFW_KEY_A])
    moveBy -= camera->Right * (GLfloat)(this->speed * delta);
    if(keys[GLFW_KEY_D])
    moveBy += camera->Right * (GLfloat)(this->speed * delta);

    return moveBy;
};
//
//void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
//{
//    GLfloat velocity = this->MovementSpeed * deltaTime;
//    if (direction == FORWARD)
//        this->Position += this->Front * velocity;
//    if (direction == BACKWARD)
//        this->Position -= this->Front * velocity;
//    if (direction == LEFT)
//        this->Position -= this->Right * velocity;
//    if (direction == RIGHT)
//        this->Position += this->Right * velocity;
//
//    this->Position.y = 0;
//}

