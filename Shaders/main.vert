#version 330 core
layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 1) in vec2 tex; // The position variable has attribute position 0

out vec4 TexCoord; // Specify a color output to the fragment shader


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0); // See how we directly give a vec3 to vec4's constructor
    TexCoord = vec4(position, 1.0);
}