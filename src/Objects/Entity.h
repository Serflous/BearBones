#pragma once

#include <GLM/vec3.hpp>

#include "ObjModel.h"

namespace Objects
{

	class Entity
	{
	public:
		Entity();
		Entity(const Entity & other);
		~Entity();

		void SetModel(Objects::ObjModel model);
		void SetPosition(glm::vec3 position);
		void SetRotation(glm::vec3 rotation);
		void SetScale(glm::vec3 scale);

		Objects::ObjModel GetModel();
		glm::vec3 GetPosition();
		glm::vec3 GetRotation();
		glm::vec3 GetScale();

	private:
		Objects::ObjModel m_model;
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
	};

}