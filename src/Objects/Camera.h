#pragma once

#include <GLM/glm.hpp>
#include <GLM/vec3.hpp>

namespace Objects
{

		/**
		 * The direction to move the camera.
		 */
	enum CameraDirection
	{
		FORWARD, /** Move the camera forward. */
		BACKWARD, /** Move the camera backward. */
		LEFT, /** Strafe the camera left. */
		RIGHT /** Strafe the camera right. */
	};

		/**
		 * A first person camera. Contains the positional and rotational data about the camera.
		 * @author Mathew Causby
		 * @version 0.1
		 */
	class Camera
	{
	public:
		Camera();
		Camera(const Camera & other);
		~Camera();

			/**
			 * Gets the current position of the camera.
			 * @return The position of the camera.
			 */
		glm::vec3 GetPosition();
			/**
			 * Gets the pitch of the camera.
			 * @return The pitch of the camera.
			 * @note Pitch represents the Y axis rotation
			 */
		float GetPitch();
			/**
			 * Gets the yaw of the camera.
			 * @return The yaw of the camera.
			 * @note Yaw represents the Z axis rotation
			 */
		float GetYaw();
			/**
			 * Gets the roll of the camera.
			 * @return The roll of the camera.
			 * @note Roll represents the X axis rotation.
			 */
		float GetRoll();
			/**
			 * Gets the hover height of the camera. 
			 * @return The hover height.
			 */
		float GetHoverHeight();

			/**
			 * Sets the position of the camera.
			 * @param[in] position The position of the camera.
			 */
		void SetPosition(glm::vec3 position);
			/**
			 * Sets the position of the camera.
			 * @param[in] x The x position to set the camera to.
			 * @param[in] y The y position to set the camera to.
			 * @param[in] z The z position to set the camera to.
			 */
		void SetPosition(float x, float y, float z);
			/**
			 * Sets the rotation of the camera.
			 * @param[in] x The x rotation to apply to the camera.
			 * @param[in] y The y rotation to apply to the camera.
			 * @param[in] z The z rotation to apply to the camera.
			 */
		void SetRotation(glm::vec3 rotation);
			/**
			 * Makes the camera walk in a certain direction. Can be FORWARD or BACKWARD.
			 * @param[in] direction The direction of to walk in.
			 * @param[in] dt The delta time, provided in the update.
			 */
		void Walk(CameraDirection direction, int dt);
			/**
			 * Makes the camera strafe in a certain direction. Can be LEFT or RIGHT.
			 * @param[in] direction The direction to strafe in.
			 * @param[in] dt The delta time, provided in the update.
			 */
		void Strafe(CameraDirection direction, int dt);
			/**
			 * Rotates the camera by certain values.
			 * @param[in] dx The change in x.
			 * @param[in] dy The change in y.
			 * @param[in] dt The delta time, provided in the update.
			 */
		void Rotate(int dx, int dy, int dt);

	private:
		glm::vec3 m_position;
		float m_pitch, m_yaw, m_roll;
		float m_movementSpeed;
		float m_rotationalSpeed;
		float m_camHoverHeight;
	};

}