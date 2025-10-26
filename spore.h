#include "object.h"
#include "render_context.h"
#include "stage.h"

class Spore : public Object {
public:
    Spore(Stage* stage, vec2_t pos)
        : Object(stage, ObjectType::Enemy)
    {
        radius_ = 20.0f;
        pos_ = pos;
    }

    virtual void draw() override {
        if(!active_) {
            return;
        }
        auto context = getRenderContext();
        auto renderer = context->getRenderer();
        SDL_SetRenderDrawColor(renderer, 128, 255, 128, 255);
        SDL_FRect r = { pos_.x - radius_, pos_.y - radius_, radius_ * 2, radius_ * 2 };
        SDL_RenderFillRect(renderer, &r);
    }

    virtual void update(int64_t millisec) override {
        Object::update(millisec);
        if(pos_.y > stage_->size().y) {
            active_ = false;
        }
    }

    virtual void onHit(Object const* other) override {
        if(other->type() == ObjectType::Bullet || other->type() == ObjectType::Plane) {
            active_ = false;
        }
    }

};