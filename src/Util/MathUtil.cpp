#include "MathUtil.h"

glm::mat4x4 Util::MathUtil::GetTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
{
	glm::mat4x4 transformationMatrix(1.0f);
	transformationMatrix = glm::translate(transformationMatrix, translation);
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	transformationMatrix = glm::scale(transformationMatrix, scale);
	return transformationMatrix;
}

glm::mat4x4 Util::MathUtil::GetViewMatrix(float x, float y, float z, float pitch, float yaw, float roll)
{
	glm::mat4x4 viewMatrix(1.0f);
	viewMatrix = glm::rotate(viewMatrix, glm::radians(pitch), glm::vec3(1, 0, 0));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(yaw), glm::vec3(0, 1, 0));
	glm::vec3 negPosition(-x, -y, -z);
	viewMatrix = glm::translate(viewMatrix, negPosition);
	return viewMatrix;
}