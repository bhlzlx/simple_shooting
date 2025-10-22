#include "plane.h"

Plane::Plane(Stage* stage) : Object(stage) {
    radius_ = 10.0f;
    speed_ = 100.0f;
}
void Plane::draw() {

}

void Plane::onHit(Object const* other) {
    active_ = false;
}

bool Plane::hitTest(Object const& other) const{
    return Object::hitTest(other);
}

void Plane::shoot() {
}

