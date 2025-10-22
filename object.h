#pragma once
#include <cstdint>

class Stage;

struct vec2_t {
    float x;
    float y;
};

enum class ObjectType {
    Plane,
    Bullet,
};

class Object {
protected:
    Stage*  stage_;
    vec2_t  pos_;
    vec2_t  direction_;
    float   radius_;
    float   speed_;
    bool    active_;
public:
    Object(Stage* stage);
    void setPos(int x, int y);
    void setDirection(int x, int y);
    void setSpeed(float speed) {
        speed_ = speed;
    }
    void update(int64_t millisec);
    bool active() const {
        return active_;
    }
    virtual void draw() = 0;
    virtual bool hitTest(Object const& other) const;
    virtual void onHit(Object const* other) = 0;
};