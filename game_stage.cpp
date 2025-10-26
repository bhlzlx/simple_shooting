#include "game_stage.h"
#include "object.h"
#include "plane.h"
#include "bonus_object.h"
#include "mushroom_enemy.h"
#include <SDL3/SDL.h>

GameStage::GameStage(vec2_t size)
    : Stage(size)
    , player_(nullptr)
    , activeObjects_()
    , inactiveObjects_()
{
}

GameStage::~GameStage() {
}

bool GameStage::init() {
    if (!Stage::init()) {
        return false;
    }
    // add a plane
    auto plane = new Plane(this);
    plane->setPos({size_.x / 2, size_.y});
    plane->setSpeed(200);
    addPlayer(plane);
    // bonus
    return true;
}
void GameStage::tick(int64_t millisec) {
    if(player_) {
        Plane* plane = (Plane*)player_;
        const bool *keyStates = SDL_GetKeyboardState(NULL);
        // wasd 
        float x = 0, y = 0;
        if(keyStates[SDL_SCANCODE_W]) {
            y = -1;
        }
        if(keyStates[SDL_SCANCODE_A]) {
            x = -1;
        }
        if(keyStates[SDL_SCANCODE_S]) {
            y = 1;
        }
        if(keyStates[SDL_SCANCODE_D]) {
            x = 1;
        }
        // press j shoot
        if(keyStates[SDL_SCANCODE_J]) {
            auto bullets = plane->shoot();
            for(auto bullet : bullets) {
                addPlayerBullet(bullet);
            }
        }
        player_->setMoveDir({x, y});
    }

    Stage::tick(millisec);

    activeObjects_.clear();
    inactiveObjects_.clear();

    // player bullets hit with enemies
    for(auto bullet : playerBullets_) {
        for(auto enemy : enemies_) {
            if(bullet->active() && enemy->active()) {
                if(bullet->hitTest(enemy)) {
                    bullet->onHit(enemy);
                    enemy->onHit(bullet);
                }
            }
        }
    }
    // enemy bullets hit with player
    for(auto bullet : enemyBullets_) {
        if(bullet->active() && player_->active()) {
            if(bullet->hitTest(player_)) {
                bullet->onHit(player_);
                player_->onHit(bullet);
            }
        }
    }
    // enemy hit with player
    for(auto enemy : enemies_) {
        if(enemy->active() && player_->active()) {
            if(enemy->hitTest(player_)) {
                enemy->onHit(player_);
                player_->onHit(enemy);
            }
        }
    }
    // bonus hit with player
    for(auto bonus : bonuses_) {
        if(bonus->active() && player_->active()) {
            if(bonus->hitTest(player_)) {
                bonus->onHit(player_);
                player_->onHit(bonus);
            }
        }
    }
    // filter active objects
    for(auto object : playerBullets_) {
        if(object->active()) {
            activeObjects_.push_back(object);
        } else {
            removeObject(object);
        }
    }
    playerBullets_ = std::move(activeObjects_);
     // enemy bullets
    for(auto object : enemyBullets_) {
        if(object->active()) {
            activeObjects_.push_back(object);
        } else {
            removeObject(object);
        }
    }
    enemyBullets_ = std::move(activeObjects_);
     // enemies
    for(auto object : enemies_) {
        if(object->active()) {
            activeObjects_.push_back(object);
        } else {
            removeObject(object);
        }
    }
    enemies_ = std::move(activeObjects_);
     // bonuses
    for(auto object : bonuses_) {
        if(object->active()) {
            activeObjects_.push_back(object);
        } else {
            removeObject(object);
        }
    }
    bonuses_ = std::move(activeObjects_);
    //
    if(!player_->active()) {
        onGameOver();
    }
}

void GameStage::addObject(Object* object) {
    if(objects_.find(object) == objects_.end()) {
        Stage::addObject(object);
    }
}

void GameStage::addPlayer(Object* player) {
    if(nullptr == player_) {
        addObject(player);
        player_ = player;
    }
}

void GameStage::handleEvent(SDL_Event* event) {
    if(player_ == nullptr) {
        return;
    }
    if(event->type == SDL_EVENT_KEY_UP) {
        switch (event->key.scancode) {
            case SDL_SCANCODE_ESCAPE:
            case SDL_SCANCODE_Q:
            /* Restart the game as if the program was launched. */
            case SDL_SCANCODE_R:
                break;
            case SDL_SCANCODE_1: {
                auto bonus = new BonusObject(this, BonusType::BulletLevel, {size_.x / 2, 0});
                bonus->setMoveDir({0, 1});
                bonus->setSpeed(20);
                addObject(bonus);
                bonuses_.push_back(bonus);
                break;
            }
            case SDL_SCANCODE_2: {
                auto bonus = new BonusObject(this, BonusType::ShootLevel, {size_.x / 2, 0});
                bonus->setMoveDir({0, 1});
                bonus->setSpeed(20);
                addObject(bonus);
                bonuses_.push_back(bonus);
                break;
            }
            case SDL_SCANCODE_3: {
                auto enemy = new MushroomEnemy(this, {size_.x / 2, 90});
                // enemy->setMoveDir({0, 1});
                // enemy->setSpeed(20);
                addObject(enemy);
                enemies_.push_back(enemy);
                break;
            }
            /* Decide new direction of the snake. */
            default:
                break;
        }
    }
}

void GameStage::addEnemy(Object* enemy) {
    addObject(enemy);
    enemies_.push_back(enemy);
}
void GameStage::addBonus(Object* bonus) {
    addObject(bonus);
    bonuses_.push_back(bonus);
}
void GameStage::addPlayerBullet(Object* bullet) {
    addObject(bullet);
    playerBullets_.push_back(bullet);
}
void GameStage::addEnemyBullet(Object* bullet) {
    addObject(bullet);
    enemyBullets_.push_back(bullet);
}