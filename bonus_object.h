#include "object.h"
#include "render_context.h"

class BonusObject : public Object {
private:
    uint64_t birthTime_;
    float    birthX_;
public:
    BonusObject(Stage* stage, vec2_t pos)
        : Object(stage)
    {
        radius_ = 20.0f;
        speed_ = 0.0f;
        pos_ = pos;
        birthTime_ = SDL_GetTicks();
        birthX_ = pos_.x;
    }
    virtual void draw() override {
        if(!active_) {
            return;
        }
        auto context = getRenderContext();
        auto renderer = context->getRenderer();
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_FRect r = { pos_.x - radius_, pos_.y - radius_, radius_ * 2, radius_ * 2 };
        SDL_RenderFillRect(renderer, &r);
    }

    virtual void update(int64_t millisec) override {
        Object::update(millisec);
        auto now = SDL_GetTicks();
        auto rad = (float)(now - birthTime_) / 4000.0f;
        pos_.x = birthX_ + (float)sin(rad) * stage_->size().x / 2;
        if(pos_.y > stage_->size().y) {
            active_ = false;
        }
    }

    virtual void onHit(Object const* other) override {
        active_ = false;
    }
};