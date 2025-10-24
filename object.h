#pragma once

#include <cstdint>

class Stage;

struct vec2_t {
    float x;
    float y;
};

enum class ObjectType {
    None,
    Text,
    Plane,
    Bullet,
    Bonus,
};

enum class BonusType {
    ShootLevel, // bullet shoot interval & shoot speed
    BulletLevel, // shooting style level
};

class Object {
protected:
    Stage*  stage_;
    vec2_t  pos_;
    vec2_t  moveDir_;
    float   radius_;
    float   speed_;
    bool    active_;
    ObjectType type_;
public:
    Object(Stage* stage, ObjectType type = ObjectType::None);
    void setPos(vec2_t pos);
    void setMoveDir(vec2_t dir);
    void setSpeed(float speed) {
        speed_ = speed;
    }
    void setRadius(float val) {
        radius_ = val;
    }
    ObjectType type() const {
        return type_;
    }
    virtual void update(int64_t millisec);
    bool active() const {
        return active_;
    }
    virtual void draw() = 0;
    virtual bool hitTest(Object const& other) const;
    virtual void onHit(Object const* other) = 0;
};