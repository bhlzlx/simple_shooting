#include "plane.h"
#include "render_context.h"

Plane::Plane(Stage* stage) : Object(stage) {
    radius_ = 10.0f;
    speed_ = 100.0f;
    life_ = 5;
}
void Plane::draw() {
    if(!active_) {
        return;
    }
    auto context = getRenderContext();
    auto renderer = context->getRenderer();
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_FRect r = { pos_.x - radius_, pos_.y - radius_, radius_ * 2, radius_ * 2 };
    SDL_RenderFillRect(renderer, &r);
}

void Plane::onHit(Object const* other) {
    life_--;
    if(life_ <= 0) {
        active_ = false;
    }
}

bool Plane::hitTest(Object const& other) const{
    return Object::hitTest(other);
}

void Plane::shoot() {
}

