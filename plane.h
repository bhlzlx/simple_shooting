#pragma once
#include "object.h"
#include <cstdint>
#include <vector>

class Plane : public Object {
private:
    int                 life_;
    int                 bulletLevel_;
    int                 shootLevel_;
    int64_t             shootInterval_;
    int64_t             shootTimestamp_;
public:
    Plane(Stage* stage);
    virtual void draw();
    virtual void onHit(Object const* other);
    bool hitTest(Object const& other) const;

    void setShootLevel(int level) {
        shootLevel_ = level;
        shootInterval_ = 200 - 40 * shootLevel_;
    }
    float bulletSpeed() const {
        return shootLevel_ * 200.f + 400.f;
    }
    void setBulletLevel(int level) {
        bulletLevel_ = level;
    }
    std::vector<Object*> shoot();
};