#ifndef BALLOBJECT_H
#define BALLOBJECT_H
#include "GameObject.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture2D.h"
class BallObject :
    public GameObject
{
public:
    //球的半径
    float   Radius;
    //球是否在滑板上
    bool    Stuck;
    bool    Sticky, PassThrough;
    // constructor(s)
    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);
    // 使球移动的同时，并返回当前的位置
    glm::vec2 Move(float dt, unsigned int window_width);
    //将球重新重置回滑板上
    void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif