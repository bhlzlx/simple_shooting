#include "object.h"

#include <cmath>

Object::Object(Stage* stage, ObjectType type) {
    stage_ = stage;
    active_ = true;
    type_ = type;
    speed_ = 0.0f;
    radius_ = 0.0f;
    moveDir_ = {0, 0};
}

void Object::setPos(vec2_t pos) {
    pos_ = pos;
}
void Object::setMoveDir(vec2_t dir) {
    moveDir_ = dir;
}

void Object::update(int64_t millisec) {
    if(!active_) {
        return;
    }
    pos_.x += moveDir_.x * speed_ * (float)millisec / 1000.0f;
    pos_.y += moveDir_.y * speed_ * (float)millisec / 1000.0f;
}

bool Object::hitTest(Object const* other) const {
    if(!active_ || !other->active_) {
        return false;
    }
    auto ref = pow(other->pos_.x - pos_.x, 2) + pow(other->pos_.y - pos_.y, 2);
    if(ref < pow(radius_+other->radius_, 2)) {
        return true;
    }
    return false;
}