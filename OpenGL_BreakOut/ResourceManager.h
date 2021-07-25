#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <map>
#include <string>
#include <glad/glad.h>
#include "Texture2D.h"
#include "Shader.h"

//该类的作用用于统一管理着色器 以及纹理的生成实现等
class ResourceManager
{
public:
    // Resource storage
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;
    //用于调用创建着色器程序的函数，完成着色器的创建，存储到Shaders中，并返回该shader
    static Shader   LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name);
    // 通过shader名字来提取shader
    static Shader&   GetShader(std::string name);
    // 用于调用创建纹理的函数，完成纹理的创建，存储到Textures中，并返回该texture
    static Texture2D LoadTexture(const GLchar* file, GLboolean alpha, std::string name);
    // 通过texture名字来提取texture
    static Texture2D& GetTexture(std::string name);
    // 删除所有着色器和纹理
    static void  Clear();
private:
    
    ResourceManager() { }
    //读取着色器的GLSL文件，并生成相应的着色器程序
    static Shader    loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);
    //读取纹理的源图片文件，并生成相应的纹理
    static Texture2D loadTextureFromFile(const GLchar* file, GLboolean alpha);
};

#endif
