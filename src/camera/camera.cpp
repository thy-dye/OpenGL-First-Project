#include "camera.hpp"

Camera::Camera(const glm::vec3& origin, float hfov, float speed) 
: pos(origin), cameraSpeed(speed), hfov(hfov), forward(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f) {}

Camera::Camera(const glm::vec3& origin, const glm::vec3& forward, const glm::vec3& up, float hfov, float speed) 
: pos(origin), cameraSpeed(speed), hfov(hfov), forward(forward), up(up) {}

