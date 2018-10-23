#version 400 core

uniform vec3 primColour;

out vec4 out_Color;

void main(void)
{
	out_Color = vec4(primColour, 1.0);
}