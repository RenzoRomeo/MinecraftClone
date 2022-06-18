#include "Camera.h"

Camera::Camera()
    : position(glm::vec3(10, 2, 10)), dir(glm::vec3(1.0, 0.0, 0.0)), up(glm::vec3(0, 1, 0))
{
}

glm::mat4 Camera::getView() const
{
    return glm::lookAt(position, position + dir, up);
}

void Camera::rotateRight()
{
    dir = glm::rotate(dir, glm::radians(-180.0f * dt), glm::vec3(0, 1, 0));
}

void Camera::rotateLeft()
{
    dir = glm::rotate(dir, glm::radians(180.0f * dt), glm::vec3(0, 1, 0));
}

void Camera::moveForward()
{
    position += glm::normalize(dir) * 5.0f * dt;
}

void Camera::moveBackwards()
{
    position -= glm::normalize(dir) * 5.0f * dt;
}

void Camera::setdt(float dt)
{
    this->dt = dt;
}
