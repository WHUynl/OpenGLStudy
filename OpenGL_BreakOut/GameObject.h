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
    // 游戏物体属性（位置，大小，速率）
    glm::vec2   Position, Size, Velocity;
    //颜色
    glm::vec3   Color;
    //旋转度
    GLfloat     Rotation;
    //是否为不可击破的砖块
    GLboolean   IsSolid;
    //是否可以击毁
    GLboolean   Destroyed;
    // 该游戏物体对应的纹理
    Texture2D   Sprite;
    // Constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    // 渲染出本物体
    virtual void Draw(SpriteRenderer& renderer);
};

#endif // !GAMEOBJECT_H
