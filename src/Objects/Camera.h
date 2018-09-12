#pragma once

#include <GLM/glm.hpp>
#include <GLM/vec3.hpp>

namespace Objects
{

	enum CameraDirection
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	class Camera
	{
	public:
		Camera();
		Camera(const Camera & other);
		~Camera();

		glm::vec3 GetPosition();
		float GetPitch();
		float GetYaw();
		float GetRoll();
		float GetHoverHeight();

		void Walk(CameraDirection direction, int dx);
		void Strafe(CameraDirection direction, int dx);
		void Rotate(int dx, int dy, int dt);

	private:
		glm::vec3 m_position;
		float m_pitch, m_yaw, m_roll;
		float m_movementSpeed;
		float m_rotationalSpeed;
		float m_camHoverHeight;
	};

}