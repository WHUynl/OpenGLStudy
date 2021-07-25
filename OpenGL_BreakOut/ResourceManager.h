#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <map>
#include <string>
#include <glad/glad.h>
#include "Texture2D.h"
#include "Shader.h"

//�������������ͳһ������ɫ�� �Լ����������ʵ�ֵ�
class ResourceManager
{
public:
    // Resource storage
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;
    //���ڵ��ô�����ɫ������ĺ����������ɫ���Ĵ������洢��Shaders�У������ظ�shader
    static Shader   LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name);
    // ͨ��shader��������ȡshader
    static Shader&   GetShader(std::string name);
    // ���ڵ��ô�������ĺ������������Ĵ������洢��Textures�У������ظ�texture
    static Texture2D LoadTexture(const GLchar* file, GLboolean alpha, std::string name);
    // ͨ��texture��������ȡtexture
    static Texture2D& GetTexture(std::string name);
    // ɾ��������ɫ��������
    static void  Clear();
private:
    
    ResourceManager() { }
    //��ȡ��ɫ����GLSL�ļ�����������Ӧ����ɫ������
    static Shader    loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);
    //��ȡ�����ԴͼƬ�ļ�����������Ӧ������
    static Texture2D loadTextureFromFile(const GLchar* file, GLboolean alpha);
};

#endif
