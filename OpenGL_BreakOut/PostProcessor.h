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
    // 帧缓冲使用的shader,texture,以及指定渲染的大小
    Shader PostProcessingShader;
    Texture2D Texture;
    unsigned int Width, Height;
    // 渲染方式的选项
    bool Confuse, Chaos, Shake;
    // 初始化
    PostProcessor(Shader shader, unsigned int width, unsigned int height);
    //将帧缓冲切换到多重采样缓冲
    void BeginRender();
    //结束在多重采样缓冲的渲染后，将其数据复制到中间帧缓冲，并绑定到默认帧缓冲上，用于后面的特效处理
    void EndRender();
    // 渲染纹理
    void Render(float time);
private:
    // render state
    unsigned int MSFBO, FBO; // MSFBO = 多重采样缓冲（抗锯齿用） FBO=用于后期缓冲的中间缓冲
    unsigned int RBO; // RBO=渲染缓冲对象附件
    unsigned int VAO;
    // 初始化渲染的数据
    void initRenderData();
};

#endif