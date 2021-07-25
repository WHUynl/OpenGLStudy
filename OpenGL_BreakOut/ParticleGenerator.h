#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"
#include "Texture2D.h"
#include "GameObject.h"


// ���ӵ����ԣ�ʹ�ýṹ����
struct Particle {
    //���ӵ�λ�����ٶ�
    glm::vec2 Position, Velocity;
    //���ӵ���ɫ
    glm::vec4 Color;
    //����ʣ���ʱ��
    float     Life;

    Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};


//���Ӽ�������
class ParticleGenerator
{
public:
    // ��ʼ��ʱ��Ҫshader��texture,���ڻ������ӣ��Լ�ָ�����ӵ�����
    ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount);
    // ʹ�����������ӵ����ݽ��и���
    void Update(float dt, GameObject& object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
    // ������������
    void Draw();
private:
    //�洢���ӵ�vector
    std::vector<Particle> particles;
    unsigned int amount;
    // ���ڻ������ӵ�����ز�
    Shader shader;
    Texture2D texture;
    unsigned int VAO;
    // ��ʼ�����Ʋ������Լ����ӵ�vector
    void init();
    //�ҵ���һ��������Ч�ı��
    unsigned int firstUnusedParticle();
    // ����Ч���ӵ����ݸ���Ϊ�¼������ӵ�����
    void respawnParticle(Particle& particle, GameObject& object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};
#endif // ! PARTICLEGENERATOR_H
