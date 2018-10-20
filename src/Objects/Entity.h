#pragma once

#include <GLM/vec3.hpp>

#include <bullet/btBulletCollisionCommon.h>

#include <memory>

#include "ObjModel.h"

namespace Objects
{
		
		/**
		 * An abstract class that describes an entity. The entity allows multiple drawings of an object without having to load it in multiple times.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class Entity
	{
	public:
		Entity();
		Entity(const Entity & other);
		~Entity();

			/**
			 * Sets the model of the entity.
			 * @param[in] model A shared pointer to the model.
			 */
		void SetModel(std::shared_ptr<Objects::ObjModel> model);
			/**
			 * Sets the position of the entity.
			 * @param[in] position The position of the entity
			 */
		void SetPosition(glm::vec3 position);
			/**
			 * Sets the rotation of the entity.
			 * @param[in] rotation The rotation of the entity.
			 */
		void SetRotation(glm::vec3 rotation);
			/**
			 * Sets the scale of the entity.
			 * @param[in] scale The scale of the entity.
			 */
		void SetScale(glm::vec3 scale);

			/**
			 * Gets a shared pointer to the model to draw.
			 * @return The pointer to the model.
			 */
		std::shared_ptr<Objects::ObjModel> GetModel();
			/**
			 * Gets the position of the entity.
			 * @return The position of the entity.
			 */
		glm::vec3 GetPosition();
			/**
			 * Gets the rotation of the entity.
			 * @return The rotation of the entity.
			 */
		glm::vec3 GetRotation();
			/**
			 * Gets the scale of the entity.
			 * @return The scale of the entity.
			 */
		glm::vec3 GetScale();

		void SetCollisionObject(std::shared_ptr<btCollisionObject> object);

		std::shared_ptr<btCollisionObject> GetCollisionObject();

			/**
			 * Pure virtual function. Creates the bounding box. As each type of entity will have its own type of the bounding box.
			 */
		virtual void CreateBoundingBox() = 0;

	protected:
		std::shared_ptr<btCollisionObject> m_collisionObject;

	private:
		std::shared_ptr<Objects::ObjModel> m_model;
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;

	};

}