#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D
{
public:
    // 纹理的ID
    unsigned int ID;
    // 纹理图像宽高
    GLuint Width, Height; 
    // 纹理样式
    GLuint Internal_Format; // 纹理储存为何种格式
    GLuint Image_Format; // 源图的格式
    // 纹理环绕，以及插值方式
    GLuint Wrap_S; // Wrapping mode on S axis
    GLuint Wrap_T; // Wrapping mode on T axis
    GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
    GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels
    // Constructor (sets default texture modes)
    Texture2D();
    //将纹理图片集成到当前的纹理
    void Generate(GLuint width, GLuint height, unsigned char* data);
    // 绑定当前的纹理，用于激活
    void Bind() const;
};

#endif