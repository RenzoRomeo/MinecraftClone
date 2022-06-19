#include "Camera.h"

namespace MinecraftClone
{
	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
		: MovementSpeed(2.5f), MouseSensitivity(0.1f)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: MovementSpeed(2.5f), MouseSensitivity(0.1f)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 Camera::getView() const
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	void Camera::setdt(float dt)
	{
		this->dt = dt;
	}
	void Camera::processKeyboard(CameraMovement direction)
	{
		float velocity = MovementSpeed * dt;
		if (direction == CameraMovement::FORWARD)
			Position += Front * velocity;
		if (direction == CameraMovement::BACKWARD)
			Position -= Front * velocity;
		if (direction == CameraMovement::RIGHT)
			Position += Right * velocity;
		if (direction == CameraMovement::LEFT)
			Position -= Right * velocity;
	}

	void Camera::processMouse(float xoffset, float yoffset, GLboolean contrainPitch)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		if (contrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void Camera::updateCameraVectors()
	{
		glm::vec3 newDir;
		newDir.x = glm::cos(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));
		newDir.y = glm::sin(glm::radians(Pitch));
		newDir.z = glm::sin(glm::radians(Yaw)) * glm::cos(glm::radians(Pitch));

		Front = glm::normalize(newDir);
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
}
