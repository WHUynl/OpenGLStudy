#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>;
#include "GameLevel.h"
#include "PowerUp.h"

//��ŵ�ǰ����Ϸ״̬
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};
//�����ж���ײ�ķ���
enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

// typedef ��ײ���Ľ�����Ƿ���ײ������ײӰ��ķ�������������ש�����ĵķ���������
typedef std::tuple<bool, Direction, glm::vec2> Collision; // <collision?, what direction?, difference vector center - closest point>

class Game
{
public:

    //������Ϸ�Ĺؿ�
    std::vector<GameLevel> Levels;

    //���漤��ĵ���
    std::vector<PowerUp>  PowerUps;

    //���浱ǰ�Ĺؿ�
    unsigned int Level = 0;
    // ��Ϸ״̬
    GameState  State;
    GLboolean  Keys[1024];
    GLuint     Width, Height;
    // ���캯��/��������
    Game(GLuint width, GLuint height);
    ~Game();
    // ��ʼ����Ϸ״̬���������е���ɫ��/����/�ؿ���
    void Init();
    // ��Ϸѭ��
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
    //ִ����ײ��ש��
    void DoCollisions();

    //�������ɵĵ���
    void SpawnPowerUps(GameObject& block);
    void UpdatePowerUps(float dt);

    // ������Ϸ������
    void ResetLevel();
    void ResetPlayer();
};




#endif // !_GAME_

