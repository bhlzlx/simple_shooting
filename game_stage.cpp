#include "game_stage.h"
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
    arrayObjects_.clear();
    for (auto object : _objects) {
        arrayObjects_.push_back(object);
    }
    // hit test all array objects
    for (size_t i = 0; i < arrayObjects_.size(); i++) {
        for (size_t j = i + 1; j < arrayObjects_.size(); j++) {
            if (arrayObjects_[i]->hitTest(*arrayObjects_[j])) {
                // TODO: handle hit
            }
        }
    }
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
