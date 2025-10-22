#include "object.h"

#include <cmath>

Object::Object(Stage* stage) {
    stage_ = stage;
    active_ = true;
}

void Object::setPos(int x, int y) {
    pos_.x = x;
    pos_.y = y;
}
void Object::setDirection(int x, int y) {
    direction_.x = x;
    direction_.y = y;
}

void Object::update(int64_t millisec) {
    if(!active_) {
        return;
    }
    pos_.x += direction_.x * speed_ * (float)millisec / 1000.0f;
    pos_.y += direction_.y * speed_ * (float)millisec / 1000.0f;
}

bool Object::hitTest(Object const& other) const {
    if(!active_ || !other.active_) {
        return false;
    }
    auto ref = pow(other.pos_.x - pos_.x, 2) + pow(other.pos_.y - pos_.y, 2);
    if(ref < pow(radius_+other.radius_, 2)) {
        return true;
    }
    return false;
}