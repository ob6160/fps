#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in mat4 instanceMatrix;

out vec4 vertexColor;

uniform mat4 view;
//uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * instanceMatrix * vec4(position, 1.0f);
    vertexColor = vec4(0.5f, 0.0f, 0.5f, 1.0f); // Set the output variable to a dark-red color
}