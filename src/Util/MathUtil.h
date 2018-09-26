#pragma once

#include <GLM/mat4x4.hpp>
#include <GLM/vec3.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Util
{

		/**
		 * Contains mathematical helper functions.
		 * @author Mathew Causby.
		 * @version 0.1
		 */
	class MathUtil
	{
	public:
			/**
			 * Creates and retrieves a transformation matrix.
			 * @param[in] translation Where the object has moved to.
			 * @param[in] rotation How the object has rotated.
			 * @param[in] scale How the object is scaled.
			 * @return A matrix containing the translation, rotation, and scale transformationms.
			 */
		static glm::mat4x4 GetTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);
			/**
			 * Creates and retrieved a view matrix.
			 * View matrix being where the "camera" is
			 * @param[in] x The x position
			 * @param[in] y The y position
			 * @param[in] z The z position
			 * @param[in] pitch The pitch, or the y rotation.
			 * @param[in] yaw The yaw, or the z rotation.
			 * @param[in] roll The roll, or the x rotation.
			 * @return A matrix describing the transformation based on the camera.
			 */
		static glm::mat4x4 GetViewMatrix(float x, float y, float z, float pitch, float yaw, float roll);
	};

}