#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

// Gets the Texture Unit from the main function
uniform sampler2D tex;
uniform vec3 color;


void main()
{
	FragColor = vec4(color, 1.0) * texture(tex, TexCoords);
	// FragColor = texture(tex0, texCoord) * vec4(ourColor, 1.0);
	// FragColor = texture(image, TexCoords);
	// FragColor = vec4(1.0f, 0.4f, 1.0f, 1.0f);
}
