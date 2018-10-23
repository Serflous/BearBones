#pragma once

#include "ShaderBase.h"

namespace Shaders
{

	class PrimitiveShader : public ShaderBase
	{
	public:
		PrimitiveShader();
		PrimitiveShader(const PrimitiveShader & other);
		~PrimitiveShader();

		void BindAttributes();
		void GetAllUniforms();
		void LoadProjectionMatrix(glm::mat4x4 projectionMatrix);
		void LoadTransformationMatrix(glm::mat4x4 transformationMatrix);
		void LoadViewMatrix(glm::mat4x4 viewMatrix);
		void LoadColour(glm::vec3 colour);

	private:
		GLuint m_location_projectionMatrix;
		GLuint m_location_transformationMatrix;
		GLuint m_location_viewMatrix;
		GLuint m_location_colour;

	};

}