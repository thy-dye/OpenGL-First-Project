#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "all.hpp"

class Object {
public:

glm::mat4 getTransformMat4(){}

    inline const glm::vec3& addTranslation(const glm::vec3& trans) {}
    inline const glm::quat& addRotation(const glm::quat& rot) {}
    inline const glm::vec3& addScale(const glm::vec3& scale) {}

    inline const glm::vec3& getTranslation() { return translation; }
    inline const glm::quat& getRotation()    { return rotation; }
    inline const glm::vec3& getScale()       { return scale; }

    const glm::quat& getRotation() {}
    const glm::quat& getRotation() {}

private:
    glm::vec3 translation;
    glm::quat rotation;
    glm::vec3 scale;
};


class Mesh 
{

};

class HalfEdgeMesh
{

};