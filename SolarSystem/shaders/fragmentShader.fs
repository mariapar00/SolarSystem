#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform sampler2D diffuse0;
uniform sampler2D specular0;

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform Material material;
uniform PointLight pointLight;

uniform vec3 viewPos;

vec3 CalcPointLight(vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffMap, vec3 specMap);

void main()
{
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 diffMap = vec3(texture(diffuse0, TexCoord));
    vec3 specMap = vec3(texture(specular0, TexCoord));

    
    FragColor = vec4(CalcPointLight(norm, FragPos, viewDir, diffMap, specMap), 1.0);
}

vec3 CalcPointLight(vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffMap, vec3 specMap)
{
    vec3 lightDir = normalize(pointLight.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(pointLight.position - fragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic* (distance * distance));
    
    // combine results
    vec3 ambient  = pointLight.ambient  * diffMap;
    vec3 diffuse  = pointLight.diffuse  * diff * diffMap;
    vec3 specular = pointLight.specular * spec * specMap;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return vec3(ambient + diffuse + specular);
}

 