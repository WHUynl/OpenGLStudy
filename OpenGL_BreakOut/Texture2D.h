#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D
{
public:
    // �����ID
    unsigned int ID;
    // ����ͼ����
    GLuint Width, Height; 
    // ������ʽ
    GLuint Internal_Format; // ������Ϊ���ָ�ʽ
    GLuint Image_Format; // Դͼ�ĸ�ʽ
    // �����ƣ��Լ���ֵ��ʽ
    GLuint Wrap_S; // Wrapping mode on S axis
    GLuint Wrap_T; // Wrapping mode on T axis
    GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
    GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels
    // Constructor (sets default texture modes)
    Texture2D();
    //������ͼƬ���ɵ���ǰ������
    void Generate(GLuint width, GLuint height, unsigned char* data);
    // �󶨵�ǰ���������ڼ���
    void Bind() const;
};

#endif