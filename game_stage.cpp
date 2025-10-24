#include "game_stage.h"
#include "object.h"
#include "plane.h"
#include "bonus_object.h"
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
    auto bonus = new BonusObject(this, {size_.x / 2, 0});
    addObject(bonus);
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
                addObject(bullet);
            }
        }
        player_->setMoveDir({x, y});
    }

    Stage::tick(millisec);

    activeObjects_.clear();
    inactiveObjects_.clear();
    for (auto object : objects_) {
        if(object->active()) {
            activeObjects_.push_back(object);
        } else {
            inactiveObjects_.push_back(object);
        }
    }
    for(auto object : inactiveObjects_) {
        if(object == player_) {
            // game over
            continue;
        }
        removeObject(object);
        delete object;
    }
    // hit test all array objects
    for (size_t i = 0; i < activeObjects_.size(); i++) {
        for (size_t j = i + 1; j < activeObjects_.size(); j++) {
            if (activeObjects_[i]->hitTest(*activeObjects_[j])) {
                activeObjects_[i]->onHit(activeObjects_[j]);
                activeObjects_[j]->onHit(activeObjects_[i]);
            }
        }
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
    // switch (event->key.scancode) {
    //     case SDL_SCANCODE_ESCAPE:
    //     case SDL_SCANCODE_Q:
    //     /* Restart the game as if the program was launched. */
    //     case SDL_SCANCODE_R:
    //         break;
    //     /* Decide new direction of the snake. */
    //     case SDL_SCANCODE_RIGHT:
    //         x = 1;
    //         break;
    //     case SDL_SCANCODE_UP:
    //         y = -1;
    //         break;
    //     case SDL_SCANCODE_LEFT:
    //         x = -1;
    //         break;
    //     case SDL_SCANCODE_DOWN:
    //         y = 1;
    //         break;
    //     default:
    //         break;
    // }
    // player_->setDirection(x * 4, y * 4);
}
