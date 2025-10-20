#include "plane.h"

Plane::Plane(Stage* stage) : Object(stage) {
    radius_ = 10.0f;
    speed_ = 100.0f;
}
void Plane::draw() {

}

void Plane::onHit(Object const* other) {

}
bool Plane::hitTest(Object const& other) const {
    return false;
}

void Plane::shoot() {
}

