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
			 */
		void CreateBoundingBox(Util::BB_BoundingVolume type);
		void UpdateBoundingBox();
		void setAffordances(std::string key, double value);
		std::map<std::string, double> getAffordances();

	private:

		std::map<std::string, double> m_affordances;
	};

}