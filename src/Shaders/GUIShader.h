#pragma once

#include "ShaderBase.h"

namespace Shaders
{

	class GUIShader : public ShaderBase
	{
	public:
		GUIShader();
		GUIShader(const GUIShader & other);
		~GUIShader();


		/**
		* Binds all the attributes to the shader.
		*/
		void BindAttributes();
		/**
		* Gets the location of all the unfiforms in the shader.
		*/
		void GetAllUniforms();
		/**
		* Loads the transformation matrix to the shader.
		* @param[in] transformationMatrix The transformation matrix.
		*/
		void LoadTransformationMatrix(glm::mat4x4 transformationMatrix);
	private:
		GLuint m_location_transformationMatrix;
	};

}