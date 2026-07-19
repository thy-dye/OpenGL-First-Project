#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>   

enum CameraMode { FLYMODE, EDITINGMODE };
enum PerspectiveMode { PERSPECTIVE, ORTHOGRAPHIC };

class Camera 
{
public:
    // Constructors
    Camera(const glm::vec3& origin=glm::vec3(1.0f,0.0f,0.0f), int hfov=90);
    Camera(const glm::vec3& origin, const glm::vec3& forward, const glm::vec3& up, int hfov=90);
    
    // Copy constructor and assignment
    Camera(const Camera& c) = default;
    Camera& operator=(const Camera& c) = default;

    // Move constructor and assignment
    Camera(Camera&& c) = default;
    Camera& operator=(Camera&& c) = default;

    glm::mat4 lookAt() { return glm::lookAt(origin, forward, up); };

    // fucntions to change locations and direction of camera
    glm::vec3 translate(glm::vec3 v) { return origin +=v; };
    glm::vec3 rotate();
    
    // getter functions
    glm::vec3 getForward() { return forward; };
    glm::vec3 getUp() { return up; };
    glm::vec3 getOrigin() { return origin; };


private:
    glm::vec3 origin;
    glm::vec3 forward;
    glm::vec3 up;
    int hfov;
};