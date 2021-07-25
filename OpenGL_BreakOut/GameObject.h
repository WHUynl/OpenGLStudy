#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Texture2D.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SpriteRenderer.h"

class GameObject
{
public:
    // ��Ϸ�������ԣ�λ�ã���С�����ʣ�
    glm::vec2   Position, Size, Velocity;
    //��ɫ
    glm::vec3   Color;
    //��ת��
    GLfloat     Rotation;
    //�Ƿ�Ϊ���ɻ��Ƶ�ש��
    GLboolean   IsSolid;
    //�Ƿ���Ի���
    GLboolean   Destroyed;
    // ����Ϸ�����Ӧ������
    Texture2D   Sprite;
    // Constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    // ��Ⱦ��������
    virtual void Draw(SpriteRenderer& renderer);
};

#endif // !GAMEOBJECT_H
