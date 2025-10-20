#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <map>

class TextObject;

class RenderContext {
private:
    SDL_Renderer*               renderer;
    TTF_TextEngine*             textEngine;
    std::map<int, TTF_Font*>    fonts;
private:
    TTF_Font* getFont(int size);
public:
    RenderContext();
    bool init(SDL_Renderer* renderer);
    TTF_Text* createText(const char* text, int size);
    SDL_Renderer* getRenderer() { return renderer; }
    ~RenderContext();
};

extern RenderContext* getRenderContext();