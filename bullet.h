#pragma once
#include "object.h"

class Bullet : public Object {
private:
public:
    Bullet(Stage* stage);
    virtual void draw();
    virtual void onHit(Object const* other);
    virtual void update(int64_t millisec) override;
};