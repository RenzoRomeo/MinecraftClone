#include "core.h"

struct Camera
{
	glm::vec3 position;
	glm::vec3 dir;
	glm::vec3 up;
	float dt;
	float rotationSpeed;
	float movementSpeed;

	Camera();

	glm::mat4 getView() const;
	void rotateRight();
	void rotateLeft();
	void rotateUp();
	void rotateDown();
	void moveForward();
	void moveBackwards();
	void moveLeft();
	void moveRight();
	void setdt(float dt);
};