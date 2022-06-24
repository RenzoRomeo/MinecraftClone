#pragma once

#include "../core.h"

namespace MinecraftClone
{
	enum class Movement
	{
		Forward,
		Backward,
		Left,
		Right,
		Jump
	};

	class Player
	{
	public:
		Player();
		Player(const glm::vec3& position, const glm::vec3& looking_direction);

		void ProcessKeyboard(Movement movement, float dt);
		void ProcessMouse(float xoffset, float yoffset, float dt, GLboolean constrainPitch = true);
		glm::mat4 GetView() const;

		glm::vec3 GetPosition() const { return m_position; }
		glm::vec3 GetVelocity() const { return m_velocity; }
		int GetHeight() const { return m_height; }
		void SetPosition(const glm::vec3& position) { m_position = position; }
		void SetVelocity(const glm::vec3& velocity) { m_velocity = velocity; }

	private:
		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec3 m_world_up;

		float m_pitch;
		float m_yaw;

		float m_mouse_sensitivity;
		float m_movement_speed;

		glm::vec3 m_position;
		glm::vec3 m_velocity;
		const int m_height = 2;

	private:
		void UpdateVectors();
	};
}