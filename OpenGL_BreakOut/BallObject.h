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
    //��İ뾶
    float   Radius;
    //���Ƿ��ڻ�����
    bool    Stuck;
    bool    Sticky, PassThrough;
    // constructor(s)
    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);
    // ʹ���ƶ���ͬʱ�������ص�ǰ��λ��
    glm::vec2 Move(float dt, unsigned int window_width);
    //�����������ûػ�����
    void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif