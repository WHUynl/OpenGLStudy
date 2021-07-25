#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>
#include "GameObject.h"

class GameLevel
{
public:
    std::vector<GameObject> Bricks;

    GameLevel() { }
    // ���ļ��м��عؿ�
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    // ��Ⱦ�ؿ�
    void Draw(SpriteRenderer& renderer);
    // ���һ���ؿ��Ƿ������ (���зǼ�Ӳ�Ĵ�ש�����ݻ�)
    bool IsCompleted();
private:
    // ��ש�����ݳ�ʼ���ؿ�
    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};


#endif