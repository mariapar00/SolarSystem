#ifndef SUN_HPP
#define SUN_HPP

#include <glm/glm.hpp>

#include "../model.h"
#include "../light.h"


class Sun : public Model {
public:
    glm::vec3 lightColor;

    PointLight pointLight;

    Sun(glm::vec3 lightColor, 
        glm::vec3 ambient, 
        glm::vec3 diffuse, 
        glm::vec3 specular, 
        float constant,
        float linear,
        float quadratic,
        glm::vec3 position, 
        glm::vec3 size)
        : lightColor(lightColor), pointLight({ position, constant, linear, quadratic, ambient, diffuse, specular }),
        Model(pos, size) {}

    void render(Shader shader) {
        // set light color
        shader.setVec3("lightColor", lightColor);

        Draw(shader, "sun");
    }
};

#endif // !SUN_HPP