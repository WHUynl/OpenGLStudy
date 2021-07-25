#include "GameLevel.h"
#include "ResourceManager.h"
#include <fstream>
#include <sstream>


void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
    // 清空当前所有的砖块
    this->Bricks.clear();
    // 从文件中读取砖块信息
    unsigned int tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;//二维数组用于保存每行每个砖块的数字信息
    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) // read each word separated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }

}

void GameLevel::Draw(SpriteRenderer& renderer) {
    for (GameObject& tile : this->Bricks)
        if (!tile.Destroyed)
            tile.Draw(renderer);
}

bool GameLevel::IsCompleted()
{
    for (GameObject& tile : this->Bricks)
        if (!tile.IsSolid && !tile.Destroyed)
            return false;
    return true;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight) {
    unsigned int height = tileData.size();
    unsigned int width = tileData.size();
    float unit_width = levelWidth / static_cast<float>(width), unit_height = levelHeight / height;
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            if (tileData[i][j] == 1) {
                glm::vec2 pos = glm::vec2(unit_width * i, unit_height * j);
                glm::vec2 size = glm::vec2(unit_width , unit_height);
                GameObject obj = GameObject(pos, size, ResourceManager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
                obj.IsSolid = true;
                this->Bricks.push_back(obj);
            }
            else if(tileData[i][j] >= 2)
            {
                glm::vec3 color = glm::vec3(1.0f); // original: white
                if (tileData[i][j] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[i][j] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[i][j] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[i][j] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);
                glm::vec2 pos = glm::vec2(unit_width * i, unit_height * j);
                glm::vec2 size = glm::vec2(unit_width, unit_height);
                GameObject obj = GameObject(pos, size, ResourceManager::GetTexture("block"), color);
                obj.IsSolid = false;
                this->Bricks.push_back(obj);
            }
        }
    }
}