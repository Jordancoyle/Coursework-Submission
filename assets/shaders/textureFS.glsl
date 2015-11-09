#version 150

out vec4 FragColor;

in vec2 vertexTexCoordsOut;

uniform	sampler2D diffuseTexture;

void main()
{
	FragColor = texture(diffuseTexture, vertexTexCoordsOut);
}
