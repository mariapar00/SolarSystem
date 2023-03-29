#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "shader.h"

struct PointLight {
    // position
    glm::vec3 position;

    float constant;
    float linear;
    float quadratic;

    // light values
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;


    // render light into shader
    void render(Shader shader);
};


#endif // !LIGHT_H
