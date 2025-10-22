#include "game_stage.h"
#include <SDL3/SDL.h>
#include "object.h"

GameStage::GameStage(int width, int height) {
    width_ = width;
    height_ = height;
}

GameStage::~GameStage() {
}

bool GameStage::init() {
    if (!Stage::init()) {
        return false;
    }
    return true;
}
void GameStage::tick() {
    Stage::tick();
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
    switch (event->key.scancode) {
        case SDL_SCANCODE_ESCAPE:
        case SDL_SCANCODE_Q:
        /* Restart the game as if the program was launched. */
        case SDL_SCANCODE_R:
            break;
        /* Decide new direction of the snake. */
        case SDL_SCANCODE_RIGHT:
            break;
        case SDL_SCANCODE_UP:
            break;
        case SDL_SCANCODE_LEFT:
            break;
        case SDL_SCANCODE_DOWN:
            break;
        default:
            break;
    }
}
