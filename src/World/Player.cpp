#include "Player.h"

namespace MinecraftClone
{
	Player::Player()
		: m_movement_speed(5.0f), m_mouse_sensitivity(0.3f)
	{
		m_position = { 0,20,0 };
		m_front = { 1,0,0 };
		m_world_up = { 0,1,0 };
		m_up = { 0, 1, 0 };
		m_right = glm::cross(m_front, m_up);
		m_velocity = { 0,0,0 };
		m_pitch = 0.0f;
		m_yaw = 0.0f;
		UpdateVectors();
	}

	Player::Player(const glm::vec3& position, const glm::vec3& looking_direction)
		: m_movement_speed(5.0f), m_mouse_sensitivity(0.3f)
	{
		m_position = position;
		m_front = looking_direction;
		m_world_up = { 0,1,0 };
		m_up = { 0, 1, 0 };
		m_right = glm::cross(m_front, m_up);
		m_velocity = { 0,0,0 };
		m_pitch = 0.0f;
		m_yaw = 0.0f;
		UpdateVectors();
	}

	void Player::ProcessKeyboard(Movement movement, float dt)
	{
		float velocity = m_movement_speed * dt;
		if (movement == Movement::Forward)
			//m_position += glm::vec3{m_front.x* velocity, 0, m_front.z* velocity};// Ground collision
			m_position += m_front * velocity;
		if (movement == Movement::Backward)
			//m_position -= glm::vec3{ m_front.x * velocity, 0, m_front.z * velocity }; // Ground collision
			m_position -= m_front * velocity;
		if (movement == Movement::Right)
			m_position += m_right * velocity;
		if (movement == Movement::Left)
			m_position -= m_right * velocity;
		if (movement == Movement::Jump)
			m_velocity = { 0, 2, 0 }; // Just testing values
	}

	void Player::ProcessMouse(float xoffset, float yoffset, float dt, GLboolean constrainPitch)
	{
		xoffset *= m_mouse_sensitivity * dt * 25.0f;
		yoffset *= m_mouse_sensitivity * dt * 25.0f;

		m_yaw += xoffset;
		m_pitch += yoffset;

		if (constrainPitch)
		{
			if (m_pitch > 89.0f)
				m_pitch = 89.0f;
			if (m_pitch < -89.0f)
				m_pitch = -89.0f;
		}

		UpdateVectors();
	}

	glm::mat4 Player::GetView() const
	{
		return glm::lookAt(m_position, m_position + m_front, m_up);
	}

	void Player::UpdateVectors()
	{
		glm::vec3 newDir;
		newDir.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
		newDir.y = glm::sin(glm::radians(m_pitch));
		newDir.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));

		m_front = glm::normalize(newDir);
		m_right = glm::normalize(glm::cross(m_front, m_world_up));
		m_up = glm::normalize(glm::cross(m_right, m_front));
	}
}
