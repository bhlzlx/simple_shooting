#pragma once
#include "stage.h"
#include <vector>

class TextObject;

class MainMenu : public Stage {
private:
    std::vector<TextObject*> menuItems_;
    int                      selected_;
private:
    void setSelection(int index);
public:
    MainMenu(vec2_t size);
    
    virtual bool init() override;
    virtual void tick(int64_t millisec) override;
    virtual void handleEvent(SDL_Event* event) override;

    ~MainMenu();
};