#include "shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    int success;
    char infoLog[512];

    GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
        GLuint fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

        id = glCreateProgram();
        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);
        glLinkProgram(id);

        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
}

void Shader::activate() {
    glUseProgram(id);
}

std::string Shader::loadShaderSrc(const char* filepath) {
    std::ifstream file;
    std::stringstream buf;

    std::string ret = "";

    file.open(filepath);

    if (file.is_open()) {
        buf << file.rdbuf();
        ret = buf.str();
    }
    else {
        std::cout << "Could not open " << filepath << std::endl;
    }

    file.close();

    return ret;
}

GLuint Shader::compileShader(const char* filepath, GLenum type) {
    int success;
    char infoLog[512];

    GLuint ret = glCreateShader(type);
    std::string shaderSrc = loadShaderSrc(filepath);
    const GLchar* shader = shaderSrc.c_str();

    glShaderSource(ret, 1, &shader, NULL);
    glCompileShader(ret);

    glGetShaderiv(ret, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(ret, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return ret;
}

// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value); 
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(id, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(id, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]); 
}
void Shader::setVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y); 
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]); 
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z); 
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]); 
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{ 
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w); 
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}