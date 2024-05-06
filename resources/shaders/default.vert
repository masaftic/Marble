#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormals;

// Outputs the texture coordinates to the fragment shader
out vec2 TexCoords;
out vec3 Normals;
out vec3 currentPos;

uniform mat4 camMatrix; // from camera
uniform mat4 model;     


void main()
{
    currentPos = vec3(model * vec4(aPos, 1.0));

    gl_Position = camMatrix * model * vec4(aPos, 1.0);
    TexCoords = aTexCoords;

    // gets correct normals for a trandformed model
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    Normals = normalMatrix * aNormals;
}
