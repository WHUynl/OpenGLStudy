#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


// General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
class Shader
{
public:
    // 着色器的ID值
    GLuint ID;
    // Constructor
    Shader() { }
    // 激活着色器
    Shader& use();
    // 编译着色器，注意几何着色器可以为空
    void    Compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource = nullptr); // Note: geometry source code is optional 
    // 以下均用于通过程序直接给着色器赋值
    void    SetFloat(const GLchar* name, GLfloat value, GLboolean useShader = false);
    void    SetInteger(const GLchar* name, GLint value, GLboolean useShader = false);
    void    SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void    SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader = false);
    void    SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void    SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader = false);
    void    SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void    SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader = false);
    void    SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader = false);
private:
    // 检查着色器以及着色器程序是否正常编译
    void    checkCompileErrors(GLuint object, std::string type);
};

#endif