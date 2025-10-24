#include "plane.h"
#include "render_context.h"
#include "bullet.h"
#include "game_stage.h"
#include <cmath>

Plane::Plane(Stage* stage) : Object(stage, ObjectType::Plane) {
    radius_ = 10.0f;
    speed_ = 100.0f;
    life_ = 5;
    shootTimestamp_ = 0;
    setShootLevel(0);
    setBulletLevel(2);
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

std::vector<Object*> Plane::shoot() {
    auto tick = SDL_GetTicks();
    auto timeDiff = tick - shootTimestamp_;
    if(timeDiff < (uint64_t)shootInterval_) {
        return {};
    }
    shootTimestamp_ = tick;
    int count = bulletLevel_ + 1;
    std::vector<Object*> bullets;
    float rad = SDL_PI_F / (count + 1);
    for(int i = 0; i<count; ++i) {
        Bullet* bullet = new Bullet(stage_);
        bullet->setPos({pos_.x, pos_.y - 16});
        bullet->setMoveDir({cos(rad*(i+1)), -sin(rad*(i+1))});
        bullet->setSpeed(bulletSpeed());
        bullets.push_back(bullet);
    }
    return bullets;
}

