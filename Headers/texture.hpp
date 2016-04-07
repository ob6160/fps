#pragma once

#include <glad/glad.h>
#include <string>
#include <stb_image.h>

class Texture {

public:
    Texture(std::string path) {
        setId(this->load(path));
    };

    ~Texture() {};

    void bind() {
        glBindTexture(GL_TEXTURE_2D, id);
    };

    void setId(GLuint id) {
        this->id = id;
    };

    GLuint getId() {
      return id;
    };

private:
    GLuint id;

    GLuint load(std::string path) {
        int w, h, comp;

        GLuint m_texture;

        unsigned char* image = stbi_load(path.c_str(), &w, &h, &comp, STBI_default);

        if(image == nullptr)
            throw(std::string("Failed to load texture"));

        glGenTextures(1, &m_texture);

        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// Set texture wrapping to GL_REPEAT
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        // Set texture filtering
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);

        if(comp == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        else if(comp == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(image);

        return m_texture;
    };
};