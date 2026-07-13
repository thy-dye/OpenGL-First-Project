#pragma once
#include <vector>
#include "shader.hpp"
#include "texture.hpp"

struct Material {
    Shader* s;
    std::vector<texture*> textures;    
};