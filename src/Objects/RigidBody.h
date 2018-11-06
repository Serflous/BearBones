#pragma once
#include "Objects/Entity.h"
#include "bullet/btBulletCollisionCommon.h"
#include "GLM/mat3x3.hpp"
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/vec4.hpp>

namespace Objects
{
		/**
		 * An entity that can be affected by physics.
		 * @author Mathew Causby
		 * version 0.1
		 */
	class RigidBody : public Entity
	{
	public:
		RigidBody();
		RigidBody(const RigidBody & other);
		~RigidBody();

			/**
			 * Creates a Bounding Box for the rigid body.
			 * @param[in] type The type of bounding box to use.
			 */
		virtual void CreateBoundingBox(Util::BB_BoundingVolume type);
			/**
			 * Updates the Bounding Box of the rigid body.
			 */
		virtual void UpdateBoundingBox();

			/**
			 * Sets the mass of the rigid body.
			 * @param[in] mass The mass to assign to the rigid body.
			 */
		void SetMass(double mass);
			/**
			 * Sets the center of gravity of the rigid body.
			 * @param[in] cog The center of gravity to assign to the rigid body.
			 */
		void SetCenterOfGravity(glm::vec3 cog);
			/**
			 * Sets the velocity of the rigid body.
			 * @param[in] velocity The velocity at which the rigid body will travel at.
			 */
		void SetVelocity(glm::vec3 velocity);
			/**
			 * Sets the rotaional velocity of the rigid body.
			 * @param[in] rotation The rotaional velocity at which the rigid body will travel at.
			 */
		void SetRotationalVelocity(glm::vec3 rotation);

			/**
			 * Gets the mass of the rigid body.
			 * @return The mass of the rigid body.
			 */
		double GetMass();
			/**
			 * Gets the center of gravity of the rigid body.
			 * @return The center of gravity of the rigid body.
			 */
		glm::vec3 GetCenterOfGravity();
			/**
			 * Gets the velocity of the rigid body.
			 * @return The velocity that the rigid body is currently travelling at.
			 */
		glm::vec3 GetVelocity();
			/**
			 * Gets the momentum of the rigid body.
			 * @return The current momentum of the rigid body.
			 */
		glm::vec3 GetMomentum();
			/**
			 * Gets the rotational velocity of the rigid body.
			 * @return The rotational velocity that the rigid body is currently travelling at.
			 */
		glm::vec3 GetRotationalVelocity();

			/**
			 * Integrate step. Moves the entity based on current velocity and rotation.
			 * @param[in] dt The delta time, provided in the update.
			 */
		void Integrate(double dt);
			/**
			 * Applies gravity to the rigid body.
			 * @param[in] gravity The gravity to apply to the rigid body.
			 * @param[in] dt The delta time, provided in the update.
			 */
		void ApplyGravity(glm::vec3 gravity, double dt);
			/**
			 * Applies force to the rigid body.
			 * @param[in] force The force to apply to the rigid body.
			 * @param[in] dt The delta time, provided in the update.
			 */
		void ApplyForce(glm::vec3 force, double dt);
			/**
			 * Applies torque to the rigid body.
			 * @param[in] torque The torque to apply to the rigid body.
			 * @param[in] dt The delta time, provided in the update.
			 */
		void ApplyTorque(glm::vec3 torque, double dt);
		
	private:
		double m_mass;
		glm::vec3 m_cog;
		glm::vec3 m_velocity;
		glm::vec3 m_rotationalVelocity;

	};
}