#ifndef STATICSHADER_H
#define STATICSHADER_H

#include "ShaderBase.h"

namespace Shaders
{
	
	class StaticShader : public ShaderBase
	{
	public:
		StaticShader();
		StaticShader(const StaticShader & other);
		~StaticShader();

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

#endif