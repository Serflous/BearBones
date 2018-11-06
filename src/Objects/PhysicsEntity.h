#pragma once
#include "Objects/Entity.h"

namespace Objects
{
	/**
	 * An entity that is affected by physics
	 * @author Mathew Causby
	 * @version 0.1
	 */
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

		/**
		 * Creates a bounding box for the entity.
		 */
		void CreateBoundingBox()
		{

		}

		/**
		 * 
		 * @param[in] delta The delta time, provided in the update.
		 */
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



