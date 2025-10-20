#pragma once
#include "object.h"
#include <cstdint>

class Plane : public Object {
private:
    int64_t             shootInterval_;
    int64_t             timeLastShoot_;
public:
    Plane(Stage* stage);
    virtual void draw() = 0;
    virtual void onHit(Object const* other) = 0;
    void setPos(int x, int y);
    void setDirection(int x, int y);
    void update(float deltaTime);
    bool hitTest(Object const& other) const;
    void shoot();
};