#include "camera.hpp"

Camera::Camera(const glm::vec3& origin) 
: origin(origin), forward(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f) 
{

}

Camera::Camera(const glm::vec3& origin, const glm::vec3& forward, const glm::vec3& up) 
: origin(origin), forward(forward), up(up)
{

}

