#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

// Outputs the texture coordinates to the fragment shader
out vec2 TexCoords;

uniform mat4 camMatrix; // from camera
uniform mat4 model;     // from CubeRenderer


void main()
{
    gl_Position = camMatrix * model * vec4(aPos, 1.0);
    // gl_Position = model * vec4(aPos, 1.0);
    TexCoords = aTexCoords;
}
