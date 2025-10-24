#include "bullet.h"
#include "render_context.h"

Bullet::Bullet(Stage* stage)
    : Object(stage, ObjectType::Bullet)
{
    radius_ = 4.0f;
}

void Bullet::draw() {
    auto context = getRenderContext();
    auto renderer = context->getRenderer();
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_FRect r = { pos_.x - radius_, pos_.y - radius_, radius_ * 2, radius_ * 2 };
    SDL_RenderFillRect(renderer, &r);
}

void Bullet::onHit(Object const* other) {
    active_ = false;
}

void Bullet::update(int64_t millisec) {
    Object::update(millisec);
    if(pos_.y < 0) {
        active_ = false;
    }
}