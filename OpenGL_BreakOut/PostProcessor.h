#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Shader.h"


// PostProcessor hosts all PostProcessing effects for the Breakout
// Game. It renders the game on a textured quad after which one can
// enable specific effects by enabling either the Confuse, Chaos or 
// Shake boolean. 
// It is required to call BeginRender() before rendering the game
// and EndRender() after rendering the game for the class to work.
class PostProcessor
{
public:
    // ֡����ʹ�õ�shader,texture,�Լ�ָ����Ⱦ�Ĵ�С
    Shader PostProcessingShader;
    Texture2D Texture;
    unsigned int Width, Height;
    // ��Ⱦ��ʽ��ѡ��
    bool Confuse, Chaos, Shake;
    // ��ʼ��
    PostProcessor(Shader shader, unsigned int width, unsigned int height);
    //��֡�����л������ز�������
    void BeginRender();
    //�����ڶ��ز����������Ⱦ�󣬽������ݸ��Ƶ��м�֡���壬���󶨵�Ĭ��֡�����ϣ����ں������Ч����
    void EndRender();
    // ��Ⱦ����
    void Render(float time);
private:
    // render state
    unsigned int MSFBO, FBO; // MSFBO = ���ز������壨������ã� FBO=���ں��ڻ�����м仺��
    unsigned int RBO; // RBO=��Ⱦ������󸽼�
    unsigned int VAO;
    // ��ʼ����Ⱦ������
    void initRenderData();
};

#endif