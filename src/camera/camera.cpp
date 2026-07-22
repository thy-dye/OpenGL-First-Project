#include "camera.hpp"

Camera::Camera(const glm::vec3& origin, float fov, float speed) 
: pos(origin), cameraSpeed(speed), fov(fov), forward(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f) {}

Camera::Camera(const glm::vec3& origin, const glm::vec3& forward, const glm::vec3& up, float fov, float speed) 
: pos(origin), cameraSpeed(speed), fov(fov), forward(forward), up(up) {}

