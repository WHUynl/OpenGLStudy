#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>;
#include "GameLevel.h"
#include "PowerUp.h"

//存放当前的游戏状态
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};
//用于判断碰撞的方向
enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

// typedef 碰撞检测的结果（是否碰撞？，碰撞影响的方向，球体中心与砖块中心的方向向量）
typedef std::tuple<bool, Direction, glm::vec2> Collision; // <collision?, what direction?, difference vector center - closest point>

class Game
{
public:

    //储存游戏的关卡
    std::vector<GameLevel> Levels;

    //储存激活的道具
    std::vector<PowerUp>  PowerUps;

    //储存当前的关卡
    unsigned int Level = 0;
    // 游戏状态
    GameState  State;
    GLboolean  Keys[1024];
    GLuint     Width, Height;
    // 构造函数/析构函数
    Game(GLuint width, GLuint height);
    ~Game();
    // 初始化游戏状态（加载所有的着色器/纹理/关卡）
    void Init();
    // 游戏循环
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
    //执行球撞碎砖块
    void DoCollisions();

    //管理生成的道具
    void SpawnPowerUps(GameObject& block);
    void UpdatePowerUps(float dt);

    // 重置游戏的设置
    void ResetLevel();
    void ResetPlayer();
};




#endif // !_GAME_

