#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>   
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"

enum CameraMode { FLYMODE, EDITINGMODE };
enum PerspectiveMode { PERSPECTIVE, ORTHOGRAPHIC };

class Camera 
{
public:
    // Constructors
    Camera(const glm::vec3& origin=glm::vec3(1.0f,0.0f,0.0f), float hfov=90, float speed=1.5);
    Camera(const glm::vec3& origin, const glm::vec3& forward, const glm::vec3& up, float hfov=90, float speed=1.5); //maybe normalize cord
    
    // Copy constructor and assignment
    Camera(const Camera& c) = default;
    Camera& operator=(const Camera& c) = default;

    // Move constructor and assignment
    Camera(Camera&& c) = default;
    Camera& operator=(Camera&& c) = default;

    // functions about perspective or sum idk 
    glm::mat4 lookAt() { return glm::lookAt(pos, pos + forward, up); };
    glm::mat4 perspectiveProjection() { return glm::perspective(hfov, 800.0f / 600.0f, 0.1f, 100.0f); };
    glm::mat4 orthographicProjection() { return glm::orthographic(); };

    // fucntions to change locations and direction of camera
    glm::vec3 translate(glm::vec3 v) { return pos +=v; };
    glm::vec3 rotate();
    
    // getter functions
    glm::vec3 getForward() { return forward; };
    glm::vec3 getUp() { return up; };
    glm::vec3 getRight() { return glm::cross(forward, up); };
    glm::vec3 getOrigin() { return pos; };


    glm::vec3 pos;
    float cameraSpeed;
    float hfov;
private:
    glm::vec3 forward;
    glm::vec3 up;
};

struct Mouse {
    int xpos, ypos, xoffset, yoffset;
};