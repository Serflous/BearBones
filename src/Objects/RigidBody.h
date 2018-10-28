#pragma once
#include "Objects/Entity.h"
#include "bullet/btBulletCollisionCommon.h"
#include "GLM/mat3x3.hpp"
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/vec4.hpp>

namespace Objects
{
	class RigidBody : public Entity
	{
	public:
		RigidBody();
		RigidBody(const RigidBody & other);
		~RigidBody();

		virtual void CreateBoundingBox(Util::BB_BoundingVolume type);
		virtual void UpdateBoundingBox();

		void SetMass(double mass);
		void SetCenterOfGravity(glm::vec3 cog);
		void SetVelocity(glm::vec3 velocity);

		double GetMass();
		glm::vec3 GetCenterOfGravity();
		glm::vec3 GetVelocity();
		glm::vec3 GetMomentum();

		void Integrate(double dt);
		void ApplyGravity(glm::vec3 gravity, double dt);
		void ApplyForce(glm::vec3 force, double dt);
		
	private:
		double m_mass;
		glm::vec3 m_cog;
		glm::vec3 m_velocity;

	};
}