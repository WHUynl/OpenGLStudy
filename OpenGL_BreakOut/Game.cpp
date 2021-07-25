#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "BallObject.h"
#include "ParticleGenerator.h"
#include "PostProcessor.h"
#include <irrklang/irrKlang.h>
using namespace irrklang;

ISoundEngine* SoundEngine = createIrrKlangDevice();

//�ж��Ƿ���ײ
Collision  CheckCollision(BallObject& one, GameObject& two);
bool CheckCollision(GameObject& player, GameObject& powerUp);
//�ж���ײ���ķ���
Direction VectorDirection(glm::vec2 target);
//�����Ƿ����ɵ���
bool PowerUpChance(int chance);
//�������
void ActivatePowerUp(PowerUp& powerUp);
//���ͬ���͵����Ƿ�ʱ���Ѿ�����
bool IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type);

Game::Game(GLuint width, GLuint height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}


float ShakeTime = 0.0f;

SpriteRenderer* Renderer;

// ��ʼ������Ĵ�С
const glm::vec2 PLAYER_SIZE(100, 20);
// ��ʼ�����������
const GLfloat PLAYER_VELOCITY(500.0f);
//��Ҷ���
GameObject* Player;
//�����
BallObject* Ball;
// ��ʼ������ٶ�
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// ��İ뾶
const GLfloat BALL_RADIUS = 12.5f;

//���Ӽ�����
ParticleGenerator* Particles;
//��Ч��
PostProcessor* Effects;

void Game::Init()
{
    // ������ɫ��
    ResourceManager::LoadShader("sprite.vs", "sprite.fs", nullptr, "sprite");
    ResourceManager::LoadShader("particle.vs", "particle.fs", nullptr, "particle");
    ResourceManager::LoadShader("post_processing.vs", "post_processing.fs", nullptr, "postprocessing");
    // ��������
    ResourceManager::LoadTexture("awesomeface.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture("block_solid.png", GL_FALSE, "block_solid");
    ResourceManager::LoadTexture("background.jpg", GL_FALSE, "background");
    ResourceManager::LoadTexture("paddle.png", GL_TRUE, "paddle");
    ResourceManager::LoadTexture("particle.png", GL_TRUE, "particle");
    ResourceManager::LoadTexture("powerup_chaos.png", GL_TRUE, "powerup_chaos");
    ResourceManager::LoadTexture("powerup_confuse.png", GL_TRUE, "powerup_confuse");
    ResourceManager::LoadTexture("powerup_increase.png", GL_TRUE, "powerup_increase");
    ResourceManager::LoadTexture("powerup_passthrough.png", GL_TRUE, "powerup_passthrough");
    ResourceManager::LoadTexture("powerup_speed.png", GL_TRUE, "powerup_speed");
    ResourceManager::LoadTexture("powerup_sticky.png", GL_TRUE, "powerup_sticky");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
        static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").use().SetMatrix4("projection", projection);
    ResourceManager::GetShader("sprite").SetInteger("image", 0);

    ResourceManager::GetShader("particle").use().SetInteger("sprite", 0);
    ResourceManager::GetShader("particle").SetMatrix4("projection", projection);
    
    // ����ר������Ⱦ�Ŀ���
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));


    // ���عؿ�
    GameLevel one; one.Load("levels/one.lvl", this->Width, this->Height * 0.5);
    GameLevel two; two.Load("levels/two.lvl", this->Width, this->Height * 0.5);
    GameLevel three; three.Load("levels/three.lvl", this->Width, this->Height * 0.5);
    GameLevel four; four.Load("levels/four.lvl", this->Width, this->Height * 0.5);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;

    //��ʼ�����
    glm::vec2 playerPos;
    Player = new GameObject(playerPos= glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y), PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
    
    //��ʼ����
    Ball = new BallObject(playerPos + glm::vec2(PLAYER_SIZE.x/2-BALL_RADIUS, -BALL_RADIUS * 2), BALL_RADIUS, INITIAL_BALL_VELOCITY,
            ResourceManager::GetTexture("face"));

    Particles = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), 1200);

    Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->Width, this->Height);

    //��������
    SoundEngine->play2D("breakout.mp3", GL_TRUE);
}

void Game::Update(GLfloat dt)
{
    if (this->State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        Ball->Move(dt, this->Width);
        this->DoCollisions();

        if (Ball->Position.y >= this->Height) // ���Ƿ�Ӵ��ײ��߽磿
        {
            this->ResetLevel();
            this->ResetPlayer();
        }
        Particles->Update(dt, *Ball,2, glm::vec2(Ball->Radius / 2));
        if (ShakeTime > 0.0f)
        {
            ShakeTime -= dt;
            if (ShakeTime <= 0.0f)
                Effects->Shake = false;
        }
        UpdatePowerUps(dt);
    }
}


void Game::ProcessInput(GLfloat dt)
{
    if (this->State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // �ƶ���ҵ���
        if (this->Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0)
            {
                Player->Position.x -= velocity;
                if (Ball->Stuck)
                    Ball->Position.x -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
            {
                Player->Position.x += velocity;
                if (Ball->Stuck)
                    Ball->Position.x += velocity;
            }
        }
        if (this->Keys[GLFW_KEY_SPACE])
            Ball->Stuck = false;
    }
}

void Game::Render()
{

    if (this->State == GAME_ACTIVE)
    {

        Effects->BeginRender();

        // ���Ʊ���
        Renderer->DrawSprite(ResourceManager::GetTexture("background"),
            glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
        );
        // ���ƹؿ�
        this->Levels[this->Level].Draw(*Renderer);
        Player->Draw(*Renderer);
        //��������
        Particles->Draw();
        //������
        Ball->Draw(*Renderer);
        //���Ƶ���
        for (PowerUp& it : PowerUps) {
            if (!it.Destroyed) {
                it.Draw(*Renderer);
            }
        }

        Effects->EndRender();
        Effects->Render(glfwGetTime());
    }

}


void Game::DoCollisions() {
    //�ж����뷽�����ײ���
    for (GameObject& box : Levels[this->Level].Bricks) {
        if (!box.Destroyed)
        {
            Collision collision = CheckCollision(*Ball, box);
            if (std::get<0>(collision))
            {
                // ���ש�鲻��ʵ�ľ�����ש��
                if (!box.IsSolid) {
                    SoundEngine->play2D("bleep.mp3", false);
                    box.Destroyed = GL_TRUE;
                    SpawnPowerUps(box);
                }
                else
                {   // �����ʵ�ĵ�ש���򼤻�shake��Ч
                    ShakeTime = 0.05f;
                    Effects->Shake = true;
                    SoundEngine->play2D("solid.wav", false);
                }
                if(Ball->PassThrough == GL_TRUE && !box.IsSolid){
                }
                else
                {
                    Direction dir = std::get<1>(collision);
                    glm::vec2 diff_vector = std::get<2>(collision);
                    // ˮƽ������ײ
                    if (dir == LEFT || dir == RIGHT) {
                        //ˮƽ�ٶȷ���
                        Ball->Velocity.x *= -1.0f;
                        //����ض�λ
                        float penetration = Ball->Radius - std::abs(diff_vector.x);
                        if (dir == LEFT)
                            Ball->Position.x += penetration; // ��������
                        else
                            Ball->Position.x -= penetration; // ��������
                    }
                    else
                    {
                        Ball->Velocity.y = -Ball->Velocity.y; // ��ת��ֱ�ٶ�
                        // �ض�λ
                        float penetration = Ball->Radius - std::abs(diff_vector.y);
                        if (dir == UP)
                            Ball->Position.y -= penetration; // ��������
                        else
                            Ball->Position.y += penetration; // ��������
                    }
                }

            }
        }
    }
    //�ж����뵲�����ײ���
    Collision result = CheckCollision(*Ball, *Player);
    if (!Ball->Stuck && std::get<0>(result))
    {
        // ��������˵�����ĸ�λ�ã������������ĸ�λ�����ı��ٶ�
        GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
        GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
        GLfloat percentage = distance / (Player->Size.x / 2);
        // ���ݽ���ƶ�
        GLfloat strength = 2.0f;
        glm::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
        Ball->Velocity.y = -1 * abs(Ball->Velocity.y);
        Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
        Ball->Stuck = Ball->Sticky;

        SoundEngine->play2D("bleep.wav", false);
    }
    //�ж�������ߵ���ײ���
    for (PowerUp& powerUp : this->PowerUps)
    {
        if (!powerUp.Destroyed)
        {
            if (powerUp.Position.y >= this->Height) {
                powerUp.Destroyed = GL_TRUE;
            }
               
            if (CheckCollision(*Player,powerUp)){   
                // �����뵲��Ӵ�����������
                ActivatePowerUp(powerUp);
                powerUp.Destroyed = GL_TRUE;
                powerUp.Activated = GL_TRUE;
                SoundEngine->play2D("powerup.wav", false);
            }
        }
    }
}


void Game::ResetLevel() {
    if (this->Level == 0)
        this->Levels[0].Load("levels/one.lvl", this->Width, this->Height / 2);
    else if (this->Level == 1)
        this->Levels[1].Load("levels/two.lvl", this->Width, this->Height / 2);
    else if (this->Level == 2)
        this->Levels[2].Load("levels/three.lvl", this->Width, this->Height / 2);
    else if (this->Level == 3)
        this->Levels[3].Load("levels/four.lvl", this->Width, this->Height / 2);
}
void Game::ResetPlayer() {
    // reset player/ball stats
    Player->Size = PLAYER_SIZE;
    Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
    // also disable all active powerups
    Ball->PassThrough = Ball->Sticky = false;
    Player->Color = glm::vec3(1.0f);
    Ball->Color = glm::vec3(1.0f);
}


void Game::SpawnPowerUps(GameObject& block) {
    if (PowerUpChance(4)) {
        this->PowerUps.push_back(PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_speed")));
    }
    else if (PowerUpChance(4)) {
        this->PowerUps.push_back(PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 10.0f, block.Position, ResourceManager::GetTexture("powerup_sticky")));
    }
        
    else if (PowerUpChance(4)) {
        this->PowerUps.push_back(PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.Position, ResourceManager::GetTexture("powerup_passthrough")));
    }
        
    else if (PowerUpChance(4)) {
        this->PowerUps.push_back(PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4), 0.0f, block.Position, ResourceManager::GetTexture("powerup_increase")));
    }
       
    else if (PowerUpChance(10)) { // Negative powerups should spawn more often
        this->PowerUps.push_back(PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_confuse")));
    }
    else if (PowerUpChance(10)) {
        this->PowerUps.push_back(PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_chaos")));
    }
}
void Game::UpdatePowerUps(float dt) {
    for (PowerUp& it : PowerUps) {
        it.Position += it.Velocity * dt;
        if (it.Activated)
        {
            it.Duration -= dt;
        }
        if (it.Duration < 0) {
            it.Activated = GL_FALSE;
            //ֹͣ��ǰӵ�е�Ч��
            if (it.Type == "sticky")
            {
                if (!IsOtherPowerUpActive(this->PowerUps, "sticky"))
                {   // ����û������stickyЧ�����ڼ���״̬ʱ���ã�����ͬ��
                    Ball->Sticky = GL_FALSE;
                    Player->Color = glm::vec3(1.0f);
                }
            }
            else if (it.Type == "pass-through")
            {
                if (!IsOtherPowerUpActive(this->PowerUps, "pass-through"))
                {
                    Ball->PassThrough = GL_FALSE;
                    Ball->Color = glm::vec3(1.0f);
                }
            }
            else if (it.Type == "confuse")
            {
                if (!IsOtherPowerUpActive(this->PowerUps, "confuse"))
                {
                    Effects->Confuse = GL_FALSE;
                }
            }
            else if (it.Type == "chaos")
            {
                if (!IsOtherPowerUpActive(this->PowerUps, "chaos"))
                {
                    Effects->Chaos = GL_FALSE;
                }
            }
        }
    }
    this->PowerUps.erase(std::remove_if(this->PowerUps.begin(), this->PowerUps.end(),
        [](const PowerUp& powerUp) { return powerUp.Destroyed && !powerUp.Activated; }
    ), this->PowerUps.end());
}

//AABB-Բ����ײ���
Collision  CheckCollision(BallObject& one, GameObject& two){
    //������ĵ��λ��
    glm::vec2 center(one.Position + one.Radius);
    // ����AABB����Ϣ�����ġ���߳���
    glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
    glm::vec2 aabb_center(
        two.Position.x + aabb_half_extents.x,
        two.Position.y + aabb_half_extents.y
    );
    // ��ȡ�������ĵĲ�ʸ��
    glm::vec2 difference = center - aabb_center;
    //clamped�Ľ��ͼ���ײ�ڶ���
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // AABB_center����clamped�����͵õ�����ײ���Ͼ���Բ����ĵ�closest
    glm::vec2 closest = aabb_center + clamped;
    // ���Բ��center�������closest��ʸ�����ж��Ƿ� length <= radius
    difference = closest - center;
    if (glm::length(difference) < one.Radius) {
        return std::make_tuple(true, VectorDirection(difference), difference);
    }
    return std::make_tuple(false, UP, glm::vec2(0, 0));
    
}

Direction VectorDirection(glm::vec2 target){
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),  // ��
        glm::vec2(1.0f, 0.0f),  // ��
        glm::vec2(0.0f, -1.0f), // ��
        glm::vec2(-1.0f, 0.0f)  // ��
    };
    float max = 0.0f;
    GLuint best_match = -1;
    for (GLuint i = 0; i < 4; i++)
    {
        //ʹ�õ�˵ļ�����������ķ������ĸ����������
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}

bool PowerUpChance(int chance) {
    int random = (int)rand() % chance;
    return random == 0;
}

void ActivatePowerUp(PowerUp& powerUp) {
    // ���ݵ������ͷ�������
    if (powerUp.Type == "speed")
    {
        Ball->Velocity *= 1.2;
    }
    else if (powerUp.Type == "sticky")
    {
        Ball->Sticky = GL_TRUE;
        Player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
    }
    else if (powerUp.Type == "pass-through")
    {
        Ball->PassThrough = GL_TRUE;
        Ball->Color = glm::vec3(1.0f, 0.5f, 0.5f);
    }
    else if (powerUp.Type == "pad-size-increase")
    {
        Player->Size.x += 50;
    }
    else if (powerUp.Type == "confuse")
    {
        if (!Effects->Chaos)
            Effects->Confuse = GL_TRUE; // ֻ��chaosδ����ʱ��Ч��chaosͬ��
    }
    else if (powerUp.Type == "chaos")
    {
        if (!Effects->Confuse)
            Effects->Chaos = GL_TRUE;
    }
}

//�������Ƿ���������
bool CheckCollision(GameObject& one, GameObject& two) {
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    // Collision y-axis?
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;
    // Collision only if on both axes
    return collisionX && collisionY;
}

bool IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type)
{
    for (const PowerUp& powerUp : powerUps)
    {
        if (powerUp.Activated)
            if (powerUp.Type == type)
                return true;
    }
    return false;
}

Game::~Game()
{
    delete Renderer;
    delete Player;
    delete Ball;
    delete Particles;
    SoundEngine->drop();
}