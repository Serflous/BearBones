#pragma once

#include "../Objects/Entity.h"
#include "GLM/glm.hpp"
#include <math.h>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/vec4.hpp>

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
		 * Changes the emotional state vector of the AI.
		 * @param[in] change The vector to change the emotional state vector.
		 */
		void ChangeEmotionalState(glm::vec2 change);

		/**
		 * Takes the current emotional state of the AI to print its overall emotional state to the console.
		 * @return String stating the AI's current emotional state.
		 */
		std::string GetEmotionalStateAsString();

		/**
		 * Gets the time the AI has to wait for.
		 * @return Amount of time for the AI to wait.
		 */
		float GetWaitTime();

		/**
		 * Creates a bounding box for the AI.
		 * @param type The type of bounding box to use.
		 */
		virtual void CreateBoundingBox(Util::BB_BoundingVolume type);

		/**
		 * Updates the AI's bounding box position.
		 */
		virtual void UpdateBoundingBox();

	private:
		float m_movementSpeed = 5.0f; // The speed of the AI - 1 means 1 unit per second.
		float m_waitTime = 2.0f; // The number of seconds the AI waits before moving to a new waypoint in seconds.
		glm::vec3 m_destination; // The current destination the AI is headed to.
		glm::vec2 m_emotionalState; // The current state of emotion of the AI - represented by Plutchik's Wheel of Emotions.
	};

}