#pragma once

#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/vec4.hpp>

#include "Entity.h"
#include "../Collision/AABB.h"

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
		void CreateBoundingBox();
		Collision::AABB GetBoundingBox();

	private:
		Collision::AABB m_boundingBox;
	};

}