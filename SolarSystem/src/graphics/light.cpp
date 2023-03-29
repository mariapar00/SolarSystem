#include "light.h"


// render point light into shader
void PointLight::render(Shader shader) {
    std::string name = "pointLight";

    shader.setVec3(name + ".position", position);

    shader.setFloat(name + ".constant", constant);
    shader.setFloat(name + ".linear", linear);
    shader.setFloat(name + ".quadratic", quadratic);

    shader.setVec3(name + ".ambient", ambient);
    shader.setVec3(name + ".diffuse", diffuse);
    shader.setVec3(name + ".specular", specular);
}


