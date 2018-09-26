#include "Camera.h"

Objects::Camera::Camera()
{
	m_pitch = 0;
	m_yaw = 0;
	m_roll = 0;
	m_movementSpeed = 0.036f;
	m_rotationalSpeed = 0.001f;
	m_camHoverHeight = 2.0f;
}

Objects::Camera::Camera(const Camera & other)
{
	m_pitch = other.m_pitch;
	m_yaw = other.m_yaw;
	m_roll = other.m_roll;
	m_movementSpeed = other.m_movementSpeed;
	m_rotationalSpeed = other.m_rotationalSpeed;
	m_camHoverHeight = other.m_camHoverHeight;
	m_position = other.m_position;
}

Objects::Camera::~Camera()
{

}

glm::vec3 Objects::Camera::GetPosition()
{
	return m_position;
}

float Objects::Camera::GetPitch()
{
	return m_pitch;
}

float Objects::Camera::GetYaw()
{
	return m_yaw;
}

float Objects::Camera::GetRoll()
{
	return m_roll;
}

float Objects::Camera::GetHoverHeight()
{
	return m_camHoverHeight;
}

void Objects::Camera::SetPosition(glm::vec3 position)
{
	m_position = position;
}

void Objects::Camera::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void Objects::Camera::Walk(CameraDirection direction, int dt)
{
	if (direction == FORWARD)
	{
		m_position.x += (float)(sin(glm::radians(m_yaw))) * m_movementSpeed * dt;
		m_position.z -= (float)(cos(glm::radians(m_yaw))) * m_movementSpeed * dt;
	}
	else if (direction == BACKWARD)
	{
		m_position.x -= (float)(sin(glm::radians(m_yaw))) * m_movementSpeed * dt;
		m_position.z += (float)(cos(glm::radians(m_yaw))) * m_movementSpeed * dt;
	}
}

void Objects::Camera::Strafe(CameraDirection direction, int dt)
{
	if (direction == LEFT)
	{
		m_position.x -= (float)(cos(glm::radians(m_yaw))) * m_movementSpeed * dt;
		m_position.z -= (float)(sin(glm::radians(m_yaw))) * m_movementSpeed * dt;
	}
	else if (direction == RIGHT)
	{
		m_position.x += (float)(cos(glm::radians(m_yaw))) * m_movementSpeed * dt;
		m_position.z += (float)(sin(glm::radians(m_yaw))) * m_movementSpeed * dt;
	}
}

void Objects::Camera::Rotate(int dx, int dy, int dt)
{
	m_yaw += dx * m_rotationalSpeed * dt;
	m_pitch += dy * m_rotationalSpeed * dt;
	if (m_yaw > 360)
		m_yaw = 0;
	if (m_yaw < 0)
		m_yaw = 360;
	if (m_pitch > 90)
		m_pitch = 90;
	if (m_pitch < -90)
		m_pitch = -90;
}