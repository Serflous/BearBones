#pragma once
#include "Collision/AABB.h"
#include "Objects/Entity.h"

namespace Objects
{
	class PhysicsEntity : public Entity
	{
	public:
		PhysicsEntity()
		{
			m_mass = 1;
			m_volume = 0;
			m_lift = 0;
			m_speed = 0;
		}

		virtual ~PhysicsEntity()
		{

		}

		void CreateBoundingBox()
		{

		}

		void Integreate(float delta)
		{
			m_position += m_velocity * delta;
		}
		//virtual matrix4x4 GetTransformation() = 0;

	protected:
		float m_mass;
		float m_massInv;
		float m_volume;
		float m_lift;
		float m_speed;

		glm::vec3 m_oldPosition;
		glm::vec3 m_position;

		glm::vec3 m_force;
		glm::vec3 m_velocity;
		glm::vec3 m_acceleration;

		glm::vec3 m_liftVector;
	};
}



