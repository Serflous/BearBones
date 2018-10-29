#pragma once

#include "Entity.h"
#include "GLM/glm.hpp"
#include <math.h>

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

		float GetWaitTime();

		void ChangeEmotionalState(glm::vec2 change);

		std::string GetEmotionalStateAsString();

		/**
		 * Creates the bounding box of the AI.
		 */
		virtual void CreateBoundingBox(Util::BB_BoundingVolume type);
		virtual void UpdateBoundingBox();

	private:
		float m_movementSpeed = 5.0f; //the speed of the ai - 1 means 1 unit per second
		float m_waitTime = 2.0f; //the number of seconds the ai waits before moving to a new waypoint in secondss
		glm::vec3 m_destination; //the current destination the AI is headed to
		glm::vec2 m_emotionalState; //the current state of emotion of the AI - represented by plutchik's wheel of emotions
	};

}