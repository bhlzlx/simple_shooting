#pragma once
#include "object.h"
#include <cstdint>

class Plane : public Object {
private:
    int                 life_;
    int64_t             shootInterval_;
    int64_t             timeLastShoot_;
public:
    Plane(Stage* stage);
    virtual void draw();
    virtual void onHit(Object const* other);
    // void update(float deltaTime);
    bool hitTest(Object const& other) const;
    void shoot();
};