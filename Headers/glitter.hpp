// Preprocessor Directives
#ifndef GLITTER
#define GLITTER
#pragma once
// System Headers
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <btBulletDynamicsCommon.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.

#include <stb_image.h>

#include <shader.hpp>
#include <GLFW/glfw3.h>
#include "camera.hpp"
#include "level.hpp"
#include "player.hpp"
#include "texture.hpp"

// Define Some Constants
static int mWidth = 1280;
static int mHeight = 800;

static float fov = 45;

static glm::mat4 view;
static glm::mat4 projection;

Camera *camera = new Camera(glm::vec3(1.5f, 0.0f,1.5f));
Player *player = new Player(glm::vec3(1.5f, 0.0f, 1.5f), camera);

Level *testLevel = new Level(100, 100);

static std::map<std::string, Texture*> textures;

bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

void setProjection(float fov, float width, float height, float near, float far);

void setView(glm::mat4 view);
void setView(glm::vec3 position, glm::vec3 lookAt, glm::vec3 direction);

void setUniforms(Shader *shader);

double _update_fps_counter (GLFWwindow* window);

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if(action == GLFW_PRESS)
            keys[key] = true;
        else if(action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) { }

void glfw_window_size_callback (GLFWwindow* window, int width, int height) {
    mWidth = width;
    mHeight = height;

    setProjection(fov, (float) mWidth, (float) mHeight, 0.001f, 10000.0f);
};

#endif
