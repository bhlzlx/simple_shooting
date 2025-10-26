#include "object.h"
#include "render_context.h"
#include <vector>
#include "game_stage.h"
#include "spore.h"
#include <cmath>

class MushroomEnemy : public Object {
public:
    uint64_t birthTime_;
    float    birthX_;
    uint64_t lastShootTime_;
    uint64_t shootInterval_;
public:
    MushroomEnemy(Stage* stage, vec2_t pos)
        : Object(stage, ObjectType::Enemy)
    {
        radius_ = 40.0f;
        pos_ = pos;
        birthTime_ = SDL_GetTicks();
        birthX_ = pos_.x;
        shootInterval_ = 1000 * 5;
    }

    void shoot() {
        auto count = 3;
        float rad = SDL_PI_F / (count + 1);
        GameStage* stage = (GameStage*)stage_;
        for(int i = 0; i<count; ++i) {
            auto pos = pos_;
            pos.y += radius_;
            Object* obj = new Spore(stage, pos);
            obj->setPos({pos_.x, pos_.y - 16});
            obj->setMoveDir({cos(rad*(i+1)), sin(rad*(i+1))});
            obj->setSpeed(100);
            stage->addEnemy(obj);
        }
    }

    virtual void draw() override {
        if(!active_) {
            return;
        }
        auto context = getRenderContext();
        auto renderer = context->getRenderer();
        SDL_SetRenderDrawColor(renderer, 106, 13, 173, 255);
        SDL_FRect r = { pos_.x - radius_, pos_.y - radius_, radius_ * 2, radius_ * 2 };
        SDL_RenderFillRect(renderer, &r);
    }

    virtual void update(int64_t millisec) override {
        Object::update(millisec);
        auto now = SDL_GetTicks();
        auto rad = (float)(now - birthTime_) / 4000.0f;
        pos_.x = birthX_ + (float)sin(rad) * stage_->size().x / 2;
        // shoot
        auto timeDiff = now - lastShootTime_;
        if(timeDiff > (uint64_t)shootInterval_) {
            shoot();
            lastShootTime_ = now;
        }
    }

    virtual void onHit(Object const* other) override {
        active_ = false;
    }

};