#pragma once
#include "stage.h"
#include <vector>

class GameStage : public Stage {
private:
    std::vector<Object*>    activeObjects_;
    std::vector<Object*>    inactiveObjects_;
    Object*                 player_;
public:
    GameStage(vec2_t size);
    ~GameStage();

    bool init() override;
    void tick(int64_t) override;
    void handleEvent(SDL_Event* event) override;

    virtual void addObject(Object* object) override;

    void addPlayer(Object* player);
};