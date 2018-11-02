#pragma once

#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/vec4.hpp>

#include <map>
#include "Entity.h"
#include <memory>
#include <string>
#include <iostream>

#include <GLM/gtc/quaternion.hpp>

namespace Objects
{

		/**
		 * A static entity is an entity that won't move or be moved by other entities.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class StaticEntity : public Entity
	{
	public:
		StaticEntity();
		StaticEntity(const StaticEntity & other);
		StaticEntity(const Entity & other);
		~StaticEntity();
			/**
			 * Creates a bounding box for the StaticEntity. Static entities use AABB.
			 * @param type The type of bounding box to use.
			 */
		void CreateBoundingBox(Util::BB_BoundingVolume type);
			/**
			 * Updates the bounding box of the StaticEntity.
			 */
		void UpdateBoundingBox();

			/**
			 * Sets the affordances of the StaticEntity.
			 * @param[in] key
			 * @param[in] value
			 */
		void SetAffordances(std::string key, double value);
			/**
			 * Sets the affordance map of the StaticEntity.
			 * @param[in] map
			 */
		void SetAffordanceMap(std::map<std::string, double> map);
			/**
			 * Gets the affordances of the StaticEntity.
			 * @return The affordances of the StaticEntity.
			 */
		std::map<std::string, double> GetAffordances();
			/**
			 * Sets the affordance of the StaticEntity.
			 * @param[in] key
			 * @return
			 */
		double GetAffordance(std::string key);


	private:

		std::map<std::string, double> m_affordances;
	};

}