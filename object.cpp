#include "object.h"

#include <cmath>

Object::Object(Stage* stage) {
    stage_ = stage;
}

void Object::setPos(int x, int y) {
    pos_.x = x;
    pos_.y = y;
}
void Object::setDirection(int x, int y) {
    direction_.x = x;
    direction_.y = y;
}

void Object::update(float deltaTime) {
    pos_.x += direction_.x * speed_ * deltaTime;
    pos_.y += direction_.y * speed_ * deltaTime;
}

bool Object::hitTest(Object const& other) const {
    auto ref = pow(other.pos_.x - pos_.x, 2) + pow(other.pos_.y - pos_.y, 2);
    if(ref < pow(size_+other.size_, 2)) {
        return true;
    }
    return false;
}