#pragma once

#include "../Objects/Entity.h"
#include "GLM/glm.hpp"
#include <GLM/gtc/matrix_transform.hpp>
//#include <GLM/vec4.hpp>
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
		 * @oaram[in] dest The location of the destination.
		 */
		void SetDestination(glm::vec3 dest);

		/**
		 * Moves the AI towards its destination based on its current speed.
		 * @return True if destination has been reached, otherwise return false until then.
		 */
		bool IncrementMovement(float deltaTime);

		/**
		 * Gets the time to wait before the AI performs another action.
		 * @return The time to wait before performing the next action.
		 */
		float GetWaitTime();

		/**
		 * Changes the current emotional state of the AI.
		 * @param[in] change 2D vector that will change the emotional state.
		 */
		void ChangeEmotionalState(glm::vec2 change);

		/**
		 * Determines the emotional state of the AI and prints a string to the console.
		 * @return String that states the AI's current emotional state.
		 */
		std::string GetEmotionalStateAsString();

		/**
		 * Creates the bounding box of the AI.
		 * @param[in] Volume of the bounding box.
		 */
		virtual void CreateBoundingBox(Util::BB_BoundingVolume volume);

		/**
		 * Updates the bounding box of the AI.
		 */
		virtual void UpdateBoundingBox();

	private:
		float m_movementSpeed = 5.0f; // The speed of the AI - 1 means 1 unit per second
		float m_waitTime = 2.0f; // The number of seconds the ai waits before moving to a new waypoint in secondss
		glm::vec3 m_destination; // The current destination the AI is headed to
		glm::vec2 m_emotionalState; // The current state of emotion of the AI - represented by plutchik's wheel of emotions
	};

}