#pragma once
#include <glm/glm.hpp>

enum CameraMode { FLYMODE, EDITINGMODE };
typedef int CameraMode;

class Camera 
{
public:

private:
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 lookat;
    glm::vec3 origin;
    CameraMode mode = FLYMODE;
};