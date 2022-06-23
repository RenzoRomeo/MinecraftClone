#include "Camera.h"

namespace MinecraftClone
{
	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
		: movement_speed(5.0f), mouse_sensitivity(0.1f)
	{
		this->position = position;
		world_up = up;
		this->yaw = yaw;
		this->pitch = pitch;
		UpdateCameraVectors();
	}

	Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: movement_speed(5.0f), mouse_sensitivity(0.1f)
	{
		position = glm::vec3(posX, posY, posZ);
		world_up = glm::vec3(upX, upY, upZ);
		this->yaw = yaw;
		this->pitch = pitch;
		UpdateCameraVectors();
	}

	glm::mat4 Camera::GetView() const
	{
		return glm::lookAt(position, position + front, up);
	}

	void Camera::SetDt(float dt)
	{
		this->dt = dt;
	}
	void Camera::ProcessKeyboard(CameraMovement direction)
	{
		float velocity = movement_speed * dt;
		if (direction == CameraMovement::Forward)
			position += front * velocity;
		if (direction == CameraMovement::Backward)
			position -= front * velocity;
		if (direction == CameraMovement::Right)
			position += right * velocity;
		if (direction == CameraMovement::Left)
			position -= right * velocity;
	}

	void Camera::ProcessMouse(float xoffset, float yoffset, GLboolean contrainPitch)
	{
		xoffset *= mouse_sensitivity;
		yoffset *= mouse_sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (contrainPitch)
		{
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}

		UpdateCameraVectors();
	}

	void Camera::UpdateCameraVectors()
	{
		glm::vec3 newDir;
		newDir.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
		newDir.y = glm::sin(glm::radians(pitch));
		newDir.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

		front = glm::normalize(newDir);
		right = glm::normalize(glm::cross(front, world_up));
		up = glm::normalize(glm::cross(right, front));
	}
}
