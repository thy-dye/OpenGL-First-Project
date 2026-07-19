#include "camera.hpp"

Camera::Camera(const glm::vec3& origin, int hfov) 
: origin(origin), forward(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f), hfov(hfov) {}

Camera::Camera(const glm::vec3& origin, const glm::vec3& forward, const glm::vec3& up, int hfov) 
: origin(origin), forward(forward), up(up), hfov(hfov) {}

