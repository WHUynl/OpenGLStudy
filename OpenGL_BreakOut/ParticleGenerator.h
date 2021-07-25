#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"
#include "Texture2D.h"
#include "GameObject.h"


// 粒子的属性，使用结构即可
struct Particle {
    //粒子的位置与速度
    glm::vec2 Position, Velocity;
    //粒子的颜色
    glm::vec4 Color;
    //粒子剩余的时间
    float     Life;

    Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};


//粒子集成器类
class ParticleGenerator
{
public:
    // 初始化时需要shader和texture,用于绘制粒子，以及指定粒子的数量
    ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount);
    // 使用球来对粒子的数据进行更新
    void Update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
    // 绘制所有粒子
    void Draw();
private:
    //存储粒子的vector
    std::vector<Particle> particles;
    unsigned int amount;
    // 用于绘制粒子的相关素材
    Shader shader;
    Texture2D texture;
    unsigned int VAO;
    // 初始化绘制部件，以及粒子的vector
    void init();
    //找到第一个粒子无效的编号
    unsigned int firstUnusedParticle();
    // 将无效粒子的数据更新为新加入粒子的数据
    void respawnParticle(Particle& particle, GameObject& object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};
#endif // ! PARTICLEGENERATOR_H
