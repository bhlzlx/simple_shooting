#include "main_menu.h"
#include <SDL3/SDL.h>
#include "text_object.h"
#include "render_context.h"

static const int MenuSizeSelect = 80;
static const int MenuSizeUnselect = 64;

MainMenu::MainMenu() {
}

void MainMenu::tick() {
    Stage::tick();
}

bool MainMenu::init() {
    if (!Stage::init()) {
        return false;
    }
    auto renderContext = getRenderContext();
    char const* items[] = {"START", "EXIT"};
    int sizes[] = {MenuSizeSelect, MenuSizeUnselect};
    for (int i = 0; i < 2; i++) {
        auto textObj = new TextObject(this, items[i], sizes[i]);
        textObj->setPos(120, (int)100 + i * 80);
        menuItems_.push_back(textObj);
        addObject(textObj);
    }
    selected_ = 0;
    return true;
}
void MainMenu::setSelection(int index) {
    index = index % menuItems_.size();
    menuItems_[selected_]->setSize(MenuSizeUnselect);
    selected_ = index;
    menuItems_[selected_]->setSize(MenuSizeSelect);
}

void MainMenu::handleEvent(SDL_Event* event) {
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
            setSelection(selected_ - 1);
            break;
        case SDL_SCANCODE_LEFT:
            break;
        case SDL_SCANCODE_DOWN:
            setSelection(selected_ + 1);
            break;
        default:
            break;
    }
}
