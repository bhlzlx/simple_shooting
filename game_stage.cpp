#include "game_stage.h"
#include "object.h"
#include "plane.h"
#include <SDL3/SDL.h>

GameStage::GameStage(int width, int height)
    : Stage()
    , player_(nullptr)
    , activeObjects_()
    , inactiveObjects_()
{
    width_ = width;
    height_ = height;
}

GameStage::~GameStage() {
}

bool GameStage::init() {
    if (!Stage::init()) {
        return false;
    }
    // add a plane
    auto plane = new Plane(this);
    plane->setPos(320, 320);
    plane->setSpeed(2);
    addPlayer(plane);
    return true;
}
void GameStage::tick(int64_t millisec) {
    if(player_) {
        const bool *keyStates = SDL_GetKeyboardState(NULL);
        // wasd 
        auto x = 0, y = 0;
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
        player_->setDirection(x, y);
    }

    Stage::tick(millisec);

    activeObjects_.clear();
    inactiveObjects_.clear();
    for (auto object : _objects) {
        if(object->active()) {
            activeObjects_.push_back(object);
        } else {
            inactiveObjects_.push_back(object);
        }
    }
    for(auto object : inactiveObjects_) {
        if(object == player_) {
            continue;
        }
    }
    // hit test all array objects
    for (size_t i = 0; i < activeObjects_.size(); i++) {
        for (size_t j = i + 1; j < activeObjects_.size(); j++) {
            if (activeObjects_[i]->hitTest(*activeObjects_[j])) {
                // TODO: handle hit
            }
        }
    }
}

void GameStage::addObject(Object* object) {
    Stage::addObject(object);
}

void GameStage::addPlayer(Object* player) {
    addObject(player);
    player_ = player;
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
