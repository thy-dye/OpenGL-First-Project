#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "halfedge.hpp"
#include "../shaders/material.hpp"
#include "../all.hpp"

class Object {
public:

// inline const glm::vec3& addTranslation(const glm::vec3& trans) {}
// inline const glm::quat& addRotation(const glm::quat& rot) {}
// inline const glm::vec3& addScale(const glm::vec3& scale) {}

const glm::vec3& getTranslation() { return pos; }
const glm::quat& getRotation()    { return rotation; }
const glm::vec3& getScale()       { return scale; }

glm::vec3 pos;
glm::quat rotation;
glm::vec3 scale;
Mesh* shape;
Material* look;
};