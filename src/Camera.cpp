#include "Camera.h"

Camera::Camera()
    : position(glm::vec3(0, 2, 0)), dir(glm::vec3(1.0, 0.0, 0.0)), up(glm::vec3(0, 1, 0)),
    rotationSpeed(250.0f), movementSpeed(5.0f)
{
}

glm::mat4 Camera::getView() const
{
    return glm::lookAt(position, position + dir, up);
}

void Camera::rotateRight()
{
    dir = glm::rotate(dir, glm::radians(-rotationSpeed * dt), glm::vec3(0, 1, 0));
}

void Camera::rotateLeft()
{
    dir = glm::rotate(dir, glm::radians(rotationSpeed * dt), glm::vec3(0, 1, 0));
}

void Camera::rotateUp()
{
    glm::vec3 axis = glm::cross(up, dir);
    dir = glm::rotate(dir, glm::radians(rotationSpeed * dt), axis);
}

void Camera::rotateDown()
{
    glm::vec3 axis = glm::cross(up, dir);
    dir = glm::rotate(dir, glm::radians(-rotationSpeed * dt), axis);
}

void Camera::moveForward()
{
    position += glm::normalize(dir) * movementSpeed * dt;
}

void Camera::moveBackwards()
{
    position -= glm::normalize(dir) * movementSpeed * dt;
}

void Camera::moveLeft()
{
    glm::vec3 axis = glm::cross(up, dir);
    position += axis * movementSpeed * dt;
}

void Camera::moveRight()
{
    glm::vec3 axis = glm::cross(up, dir);
    position -= axis * movementSpeed * dt;
}

void Camera::setdt(float dt)
{
    this->dt = dt;
}
