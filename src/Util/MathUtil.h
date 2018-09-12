#pragma once

#include <GLM/mat4x4.hpp>
#include <GLM/vec3.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Util
{

	class MathUtil
	{
	public:
		static glm::mat4x4 GetTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);
		static glm::mat4x4 GetViewMatrix(float x, float y, float z, float pitch, float yaw, float roll);
	};

}