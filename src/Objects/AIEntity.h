#pragma once

#include "Entity.h"

namespace Objects
{
		/**
		 * An AI entity is an entity that operates independently through its own unique behaviour.
		 * @author Jonathan Sands
		 * @version 0.1
		 */
	class AIEntity : public Entity
	{
	public:
		AIEntity();
		~AIEntity();

		/**
		 * Sets the destination that the AI must go to.
		 * @oaram[in] dest The location of the destination
		 */
		void SetDestination(glm::vec3 dest);

		/**
		 * Moves the AI towards its destination based on its current speed.
		 * @return True if destination has been reached, otherwise return false until then.
		 */
		bool IncrementMovement(float deltaTime);

		/**
		 * Creates the bounding box of the AI.
		 */
		void CreateBoundingBox();

	private:
		float m_movementSpeed = 0.001f;
		glm::vec3 destination;
	};

}