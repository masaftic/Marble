#version 330 core

in vec2 TexCoords;
in vec3 Normals;
in vec3 currentPos;

out vec4 FragColor;

uniform sampler2D tex;
uniform vec3 color;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;



void main()
{
	///// alot of light calculations i don't understand /////

	vec3 normal = normalize(Normals);

	                                // sun direction
	vec3 lightDirection = normalize(vec3(-10.0f, 10.0f, -10.0f));

	float ambient = 0.4f;
	float diffuse = max(dot(normal, lightDirection), 0.0f) * 0.7f;

	float specularLight = 0.5f; // Increase the specular intensity
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 26);
	float specular = specularLight * specAmount;



	FragColor = texture(tex, TexCoords) * (diffuse + ambient + specular) * lightColor;
}
