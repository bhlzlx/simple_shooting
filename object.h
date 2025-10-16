#pragma once

class Stage;

struct vec2_t {
    float x;
    float y;
};

enum ObjectType {
    Plane,
    Bullet,
};

class Object {
protected:
    Stage*  stage_;
    vec2_t  pos_;
    vec2_t  direction_;
    float   size_;
    float   speed_;
public:
    Object(Stage* stage);
    virtual void draw() = 0;
    virtual void onHit(Object const* other) = 0;
    void setPos(int x, int y);
    void setDirection(int x, int y);
    void update(float deltaTime);
    bool hitTest(Object const& other) const;
};