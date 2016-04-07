#version 330 core
layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 1) in vec3 normal; // The position variable has attribute position 0
layout (location = 2) in vec2 tex; // The position variable has attribute position 0

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out mat4 Model;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0); // See how we directly give a vec3 to vec4's constructor

    TexCoord = tex;

    Model = model;

      FragPos = vec3(model * vec4(position, 1.0f));
        Normal = mat3(transpose(inverse(model))) * normal;
}