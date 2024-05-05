#version 330 core
layout (location = 0) in vec3 position;

out vec3 TexCoords;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	vec4 pos = camMatrix * model * vec4(position, 1.0f);
	gl_Position = pos.xyww;
	TexCoords = position;
}