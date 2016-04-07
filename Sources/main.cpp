// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION


int main(int argc, char *argv[]) {
    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* mWindow = glfwCreateWindow(mWidth, mHeight, "opengl-game", nullptr, nullptr);

    // Options
    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    setProjection(45.0f, (float) mWidth, (float) mHeight, 0.1f, 10000.0f);
    setView(glm::vec3(50.0f, 50.0f, 50.0f),
            glm::vec3(0.0f, 0.0f, 100.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();

    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    glfwSetWindowSizeCallback(mWindow, glfw_window_size_callback);
    glfwSetKeyCallback(mWindow, key_callback);
    glfwSetScrollCallback(mWindow, scroll_callback);
    glfwSetCursorPosCallback(mWindow, mouse_callback);
    glfwSwapInterval(1);


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Init textures
    Texture *ainsTex = new Texture("ainsley.png");
    Texture *wallTex = new Texture("wall.png");
    textures.insert(std::map<std::string, Texture*>::value_type("wall", wallTex));
    textures.insert(std::map<std::string, Texture*>::value_type("ainsley", ainsTex));


    //Init shaders
    Shader *shader = new Shader();
    shader->attach("./main.vert").attach("./main.frag").link().activate();
    shader->bind("projection", projection).bind("view", view);;


    setUniforms(shader);

    testLevel->Construct(shader);
    testLevel->getMesh().setTexture(textures["wall"]);

    std::vector<GLfloat> tempVerts {
            -1.0f, 1.0f, 0.0f,0, 0, 1,0,1,
            -1.0f,-1.0f,0.0f,0, 0, 1,1,1,
            1.0f,-1.0f,0.0f,0, 0, 1,1,0,
            1.0f,1.0f,0.0f,0, 0, 1,0,0
    };

    std::vector<GLuint> tempIndices {
            0,1,2,0,2,3
    };

    Mesh *ainsley = new Mesh(tempVerts, tempIndices, shader->get());
    ainsley->setup();
    ainsley->bind();

    ainsley->setTexture(textures["ainsley"]);

    // Rendering Loop
    double currentFrame = glfwGetTime();
    double lastFrame = currentFrame;
    double deltaTime;

    while (glfwWindowShouldClose(mWindow) == 0) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        _update_fps_counter(mWindow);

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        setUniforms(shader);

        setView(player->getCamera().GetViewMatrix());

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, mWidth, mHeight);


        glUniform1i(glGetUniformLocation(shader->get(), "ourTexture"), 0);
        glUniform3fv(glGetUniformLocation(shader->get(), "playerPos"),  1, glm::value_ptr(player->getCamera().Position));

        testLevel->getMesh().render();



        glUniform1i(glGetUniformLocation(shader->get(), "ourTexture"), 0);
        glm::vec3 look = glm::normalize(camera->Position - glm::vec3{2.0, 0.0, 2.0});
        glm::vec3 right = glm::cross(glm::vec3{0.0, 1.0, 0.0}, look);
        glm::vec3 up2 = glm::cross(look, right);
        glm::mat4 transform;
        transform[0] = glm::vec4(right, 0);
        transform[1] = glm::vec4(up2, 0);
        transform[2] = glm::vec4(look, 0);
        transform[3] = glm::vec4(glm::vec3{2.0, 0.0, 2.0}, 1);
        transform[3] = glm::vec4(glm::vec3{2.0, 0.0, 2.0}, 1);

        ainsley->Identity(transform);

        ainsley->render();
        player->Update(deltaTime, testLevel, keys);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    };


    glfwTerminate();
    return EXIT_SUCCESS;
};

double _update_fps_counter (GLFWwindow* window) {
    static double previous_seconds = glfwGetTime ();
    static int frame_count;
    double current_seconds = glfwGetTime ();
    double elapsed_seconds = current_seconds - previous_seconds;
    if (elapsed_seconds > 0.25) {
        previous_seconds = current_seconds;
        double fps = (double)frame_count / elapsed_seconds;
        char tmp[128];
        sprintf (tmp, "opengl @ fps: %.2f", fps);
        glfwSetWindowTitle (window, tmp);
        frame_count = 0;
    }
    frame_count++;

    return elapsed_seconds;
};

void setUniforms(Shader *shader) {
    shader->bind("projection", projection);
    shader->bind("view", view);
};

void setProjection(float fov, float width, float height, float near, float far) {
   projection = glm::perspective(fov, width / height, near, far);
};

void setView(glm::mat4 newView) {
    view = newView;
};

void setView(glm::vec3 position, glm::vec3 lookAt, glm::vec3 direction) {
    view = glm::lookAt(position,
                       lookAt,
                       direction);
};

