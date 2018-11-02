#pragma once

#include <GLM/vec3.hpp>

#include <memory>

#include "../Util/Types.h"
#include "ModelBase.h"
#include "../Collision/BoundingVolume.h"
#include "../Collision/AABB.h"
#include "../Collision/OBB.h"
#include <stdio.h>
#include <map>

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
		void SetModel(std::shared_ptr<Objects::ModelBase> model);
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
		std::shared_ptr<Objects::ModelBase> GetModel();
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

			/**
			 * Pure virtual function. Creates the bounding box. As each type of entity will have its own type of the bounding box.
			 */
		virtual void CreateBoundingBox(Util::BB_BoundingVolume type) = 0;
			/**
			 * Pure virtual function. Updates the bounding box.
			 */
		virtual void UpdateBoundingBox() = 0;
		
			/**
			 * Gets the entity's bounding volume.
			 * @return The entity's bounding volume.
			 */
		std::shared_ptr<Collision::BoundingVolume> GetBoundingVolume();
			/**
			 * Sets the affordances for the entity.
			 * @param[in] key
			 * @param[in] value
			 */
		void SetAffordances(std::string key, double value);
			/**
			 * Sets the affordance map for the entity.
			 * @param map
			 */
		void SetAffordanceMap(std::map<std::string, double> map);
			/**
			 * Gets the affordances of the entity.
			 */
		std::map<std::string, double> GetAffordances();

		
		
	protected:
		std::shared_ptr<Collision::BoundingVolume> m_boundingVolume;
		Util::BB_BoundingVolume m_volumeType;


	private:
		std::map<std::string, double> m_affordances;
		std::shared_ptr<Objects::ModelBase> m_model;
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
		

	};

}