#pragma once
#include <set>

#include <SDL3_ttf/SDL_ttf.h>
#include "object.h"

class Object;
class RenderContext;

class Stage {
protected:
    vec2_t                  size_;
    std::set<Object*>       objects_;
public:
    Stage(vec2_t);

    vec2_t size() const {
        return size_;
    }

    virtual bool init();

    virtual void tick(int64_t);

    virtual void addObject(Object* object) {
        objects_.insert(object);
    }
    virtual void removeObject(Object* object) {
        objects_.erase(object);
    }

    virtual void handleEvent(SDL_Event* event) = 0;

    ~Stage();

};