#include "render_context.h"
#include "ttf_data.h"

RenderContext::RenderContext() {}

RenderContext::~RenderContext() {
    for (auto iter = fonts.begin(); iter != fonts.end(); iter++) {
        TTF_CloseFont(iter->second);
    }
    TTF_DestroyRendererTextEngine(textEngine);
}

TTF_Font* RenderContext::getFont(int size) {
    auto iter = fonts.find(size);
    if(iter != fonts.end()) {
        return iter->second;
    }
    auto font = TTF_OpenFontIO(SDL_IOFromConstMem(tiny_ttf, tiny_ttf_len), true, size);
    if(font == nullptr) {
        return nullptr;
    }
    fonts[size] = font;
    return font;
}

TTF_Text* RenderContext::createText(const char* text, int size) {
    auto font = getFont(size);
    if(font == nullptr) {
        return nullptr;
    }
    return TTF_CreateText(textEngine, font, text, strlen(text));
}
bool RenderContext::init(SDL_Renderer* renderer) {
    this->renderer = renderer;
    if(!TTF_Init()) {
        exit(1);
    }
    textEngine = TTF_CreateRendererTextEngine(renderer);
    return textEngine != nullptr;
}

RenderContext context;
RenderContext* getRenderContext() {
    return &context;
}