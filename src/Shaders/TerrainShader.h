#pragma once

#include "ShaderBase.h"

namespace Shaders
{

	class TerrainShader : public ShaderBase
	{
	public:
		TerrainShader();
		TerrainShader(TerrainShader & other);
		~TerrainShader();

		void BindAttributes();
		void GetAllUniforms();
		void LoadProjectionMatrix(glm::mat4x4 projectionMatrix);
		void LoadTransformationMatrix(glm::mat4x4 transformationMatrix);
		void LoadViewMatrix(glm::mat4x4 viewMatrix);

	private:
		GLuint m_location_projectionMatrix;
		GLuint m_location_transformationMatrix;
		GLuint m_location_viewMatrix;
	};

}