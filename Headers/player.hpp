#pragma once

#include <glm/vec3.hpp>
#include "camera.hpp"
#include "level.hpp"

class Player {
public:
    Player(glm::vec3 position, Camera *camera, float speed = 5.0f) {
        this->position = position;
        this->camera = camera;
        this->speed = speed;
    };

    void Update(double delta, Level *level, bool *keys);
    glm::vec3 HandleInput(double delta, bool *keys);

    Camera & getCamera() {
        return *camera;
    }

    ~Player() {};
private:
    glm::vec3 position;
    Camera *camera;
    float speed;
};