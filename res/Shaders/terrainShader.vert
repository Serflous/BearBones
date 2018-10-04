#version 400 core
 in vec2 position;
in vec2 textureCoords;
in vec3 normal;
 out vec2 pass_textureCoords;
 uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform sampler2D heightmapTexture;
 void main(void)
{
	
	vec4 height = texture(heightmapTexture, position);
	vec4 worldPosition = transformationMatrix * vec4(position.x, 0, position.y, 1.0);
	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	pass_textureCoords = textureCoords;
 } 