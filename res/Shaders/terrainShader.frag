#version 400 core

in vec2 pass_textureCoords;

out vec4 out_Color;

uniform sampler2D baseTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;

void main(void)
{

	out_Color = texture(baseTexture, pass_textureCoords);

}