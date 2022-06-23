#include "../core.h"


namespace MinecraftClone
{
	enum class CameraMovement
	{
		Forward,
		Backward,
		Left,
		Right
	};

	class Camera
	{
	public:
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 world_up;

		float pitch;
		float yaw;

		float dt;
		float mouse_sensitivity;
		float movement_speed;

		Camera(const glm::vec3 position = glm::vec3(0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

		glm::mat4 GetView() const;
		void SetDt(float dt);

		void ProcessKeyboard(CameraMovement direction);
		void ProcessMouse(float xoffset, float yoffset, GLboolean contrainPitch = true);

	private:
		void UpdateCameraVectors();
	};
}