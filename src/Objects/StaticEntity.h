#pragma once

#include "Entity.h"
#include "../Collision/AABB.h"

namespace Objects
{

	class StaticEntity : public Entity
	{
	public:
		StaticEntity();
		StaticEntity(const StaticEntity & other);
		StaticEntity(const Entity & other);
		~StaticEntity();
		void CreateBoundingBox();

	private:
		Collision::AABB m_boundingBox;
	};

}