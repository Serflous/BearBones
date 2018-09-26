#pragma once

#include <GLM/vec3.hpp>

namespace Collision
{
		/**
		 * An Axis Aligned Bounding Box.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class AABB
	{
	public:
		AABB();
		AABB(const AABB & other);
		~AABB();

			/**
			 * Sets the minimum bounds of the AABB
			 * @param[in] minBounds The minimum bounds.
			 */
		void SetMinBounds(glm::vec3 minBounds);
			/**
			 * Sets the minimum bounds of the AABB
			 * @param[in] x The X value
			 * @param[in] y THe Y value
			 * @param[in] z The Z value
			 */
		void SetMinBounds(float x, float y, float z);
			/**
			 * Sets the maximum bounds of the AABB
			 * @param[in] maxBounds The maximum bounds
			 */
		void SetMaxBounds(glm::vec3 maxBounds);
			/**
			* Sets the maximum bounds of the AABB
			* @param[in] x The X value
			* @param[in] y THe Y value
			* @param[in] z The Z value
			*/
		void SetMaxBounds(float x, float y, float z);

			/**
			 * Gets the minimum bounds of the AABB
			 * @return The minimum bounds
			 */
		glm::vec3 GetMinBounds();
			/**
			 * Gets the maximum bounds of the AABB
			 * @return The maximum bounds
			 */
		glm::vec3 GetMaxBounds();

	private:
		glm::vec3 m_minBounds;
		glm::vec3 m_maxBounds;
	};

}