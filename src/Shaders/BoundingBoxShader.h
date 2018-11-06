#pragma once

#include "ShaderBase.h"

namespace Shaders
{
	/**
	 * Implementation of ShaderBase defining a shader for bounding boxes.
	 * Also uploads the projection, transformation, and view matricies to the shader to create the MVP transformation.
	 * @author Mathew Causby
	 * @version 0.1
	 */
	class BoundingBoxShader : public ShaderBase
	{
	public:
		BoundingBoxShader();
		BoundingBoxShader(const BoundingBoxShader & other);
		~BoundingBoxShader();

		/**
		* Binds all the attributes to the shader.
		*/
		void BindAttributes();
		/**
		* Gets the location of all the unfiforms in the shader.
		*/
		void GetAllUniforms();
		/**
		* Loads the projection matrix to the shader.
		* @param[in] projectionMatrix The projection matrix.
		*/
		void LoadProjectionMatrix(glm::mat4x4 projectionMatrix);
		/**
		* Loads the transformation matrix to the shader.
		* @param[in] transformationMatrix The transformation matrix.
		*/
		void LoadTransformationMatrix(glm::mat4x4 transformationMatrix);
		/**
		* Loads the view matrix to the shader.
		* @param[in] viewMatrix The view matrix.
		*/
		void LoadViewMatrix(glm::mat4x4 viewMatrix);

	private:
		GLuint m_location_projectionMatrix;
		GLuint m_location_transformationMatrix;
		GLuint m_location_viewMatrix;
	};
}