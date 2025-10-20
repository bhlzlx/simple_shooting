#include "object.h"
#include "render_context.h"

class BonusObject : public Object {
public:
    BonusObject(Stage* stage)
        : Object(stage)
    {
        radius_ = 20.0f;
        speed_ = 0.0f;
    }
    virtual void draw() override {
        if(!valid_) {
            return;
        }
        auto context = getRenderContext();
        auto renderer = context->getRenderer();
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_FRect r = { pos_.x - radius_, pos_.y - radius_, radius_ * 2, radius_ * 2 };
        SDL_RenderFillRect(renderer, &r);
    }

    virtual void onHit(Object const* other) override {
        valid_ = false;
    }
};