#pragma once
#include <set>

#include <SDL3_ttf/SDL_ttf.h>

class Object;
class RenderContext;

class Stage {
protected:
    std::set<Object*> _objects;
public:
    Stage();

    virtual bool init();

    virtual void tick(int64_t);

    virtual void addObject(Object* object) {
        _objects.insert(object);
    }
    virtual void removeObject(Object* object) {
        _objects.erase(object);
    }

    virtual void handleEvent(SDL_Event* event) = 0;

    ~Stage();

};