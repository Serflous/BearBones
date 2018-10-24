#pragma once
#include "Objects/Entity.h"
#include "bullet/btBulletCollisionCommon.h"
#include "GLM/mat3x3.hpp"

namespace Objects
{
	class RigidBody : public Entity
	{
	public:
		RigidBody(float mass, glm::vec3 position, float length, float width, float height);
		RigidBody();
		RigidBody(const RigidBody & other);
		RigidBody(const Entity & other);/*
		float getMass();
		float* getLengthWidthHeight();
		float getSpeed();
		float getVolume();
		float getLift();*/

		void SetVelocity(glm::vec3 velocity);
		void SetAcceleration(glm::vec3 acceleration);
		void SetRotationalVelocity(glm::vec3 rotationalVelocity);
		void SetTorque(glm::vec3 torque);
		void SetMass(float mass);
		void SetGrounded(bool grounded);

		bool HasVelocity();

		glm::vec3 getVelocity();
		glm::vec3 GetAcceleration();
		glm::vec3 GetRotationalVelocity();
		glm::vec3 GetTorque();
		float GetMass();
		bool GetGrounded();
		
		void ApplyGravitationalForce(glm::vec3 gravity);
		void ApplyFriction(double friction);

		void CreateBoundingBox();
		void Step(float dt);
		void CalculateInertiaTensor();
		virtual ~RigidBody();

		///Actual Physics Equations Used
		/*const glm::vec3& velocity() const { return m_LinearVelocity; }

		void velocity(const glm::vec3& v) { m_LinearVelocity = v; }

		const glm::vec3& angularVelocity() const { return m_AngularVelocity; }

		void angularVelocity(const glm::vec3& v) { m_AngularVelocity = v; }

		const glm::mat3x3& inertiaTensor() const { return m_inertiaTensor; }

		const glm::mat3x3& inverseInertiaTensor() const { return m_inverseInertiaTensor; }*/

		//calculate the inertia tensor and its
		//inverse from the current orientation
		//and the principal moments of inertia

		


	private:
		/*
		float m_massInv;
		float m_volume;
		float m_lift;
		float m_speed;

		glm::mat3x3 m_inertiaTensor;
		glm::mat3x3 m_inverseInertiaTensor;

		float m_angularRotation;

		float lwh[3] = { 1, 1, 1 };
		glm::vec3 m_oldPosition;
		glm::vec3 m_position;
		glm::vec3 m_force;
		glm::vec3 m_LinearVelocity;
		glm::vec3 m_AngularVelocity;

		glm::vec3 m_liftVector;*/
		float m_mass;
		float m_width;
		float m_height;
		float m_depth;

		bool m_grounded;

		glm::vec3 m_velocity;
		glm::vec3 m_rotationalVelocity;
		glm::vec3 m_acceleration;
		glm::vec3 m_torque;
		glm::vec3 m_force;
	};
}