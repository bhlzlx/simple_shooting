#pragma once
#include "stage.h"
#include <vector>

class GameStage : public Stage {
private:
    std::vector<Object*>    activeObjects_;
    std::vector<Object*>    inactiveObjects_;
    int                     width_;
    int                     height_;
    Object*                 player_;
public:
    GameStage(int width, int height);
    ~GameStage();

    bool init() override;
    void tick() override;
    void handleEvent(SDL_Event* event) override;

    virtual void addObject(Object* object) override;

    void addPlayer(Object* player);
};