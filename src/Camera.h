#include "core.h"


namespace MinecraftClone
{
	enum class CameraMovement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	class Camera
	{
	public:
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;

		float Pitch;
		float Yaw;

		float dt;
		float MouseSensitivity;
		float MovementSpeed;

		Camera(glm::vec3 position = glm::vec3(0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

		glm::mat4 getView() const;
		void setdt(float dt);

		void processKeyboard(CameraMovement direction);
		void processMouse(float xoffset, float yoffset, GLboolean contrainPitch = true);

	private:
		void updateCameraVectors();
	};
}