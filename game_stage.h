#pragma once
#include "stage.h"
#include <vector>

class Object;

class GameStage : public Stage {
private:
    std::vector<Object*>    activeObjects_;
    std::vector<Object*>    inactiveObjects_;
    Object*                 player_;
    //
    std::vector<Object*>    playerBullets_;
    std::vector<Object*>    enemyBullets_;
    std::vector<Object*>    enemies_;
    std::vector<Object*>    bonuses_;
    //
private:
    void onGameOver() {}
public:
    GameStage(vec2_t size);
    ~GameStage();

    bool init() override;
    void tick(int64_t) override;
    void handleEvent(SDL_Event* event) override;

    virtual void addObject(Object* object) override;

    void addPlayer(Object* player);
    void addEnemy(Object* enemy);
    void addBonus(Object* bonus);
    void addPlayerBullet(Object* bullet);
    void addEnemyBullet(Object* bullet);
};