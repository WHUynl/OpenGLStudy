#include "Texture2D.h"
#include <iostream>

//对ID值进行初始化
Texture2D::Texture2D():Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR) {
	glGenTextures(1, &this->ID);
}


void  Texture2D::Generate(GLuint width, GLuint height, unsigned char* data) {
	//给纹理添加图案
	this->Width = width;
	this->Height = height;
	glBindTexture(GL_TEXTURE_2D, this->ID);

	//设置纹理的环绕以及过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);


	glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	//解绑纹理
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture2D::Bind() const {
	glBindTexture(GL_TEXTURE_2D, this->ID);
}