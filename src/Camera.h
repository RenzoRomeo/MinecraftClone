#include "core.h"

struct Camera
{
	glm::vec3 position;
	glm::vec3 dir;
	glm::vec3 up;
	float dt;

	Camera();

	glm::mat4 getView() const;
	void rotateRight();
	void rotateLeft();
	void moveForward();
	void moveBackwards();
	void setdt(float dt);
};