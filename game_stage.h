#pragma once
#include "stage.h"
#include <vector>

class GameStage : public Stage {
private:
    std::vector<Object*>    arrayObjects_;
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
};