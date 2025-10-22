#include "stage.h"
#include "object.h"
#include "render_context.h"

Stage::Stage() 
{
}

void Stage::tick(int64_t millisec) {
    for (auto object : _objects) {
        object->update(millisec);
        object->draw();
    }
}

bool Stage::init() {
    return true;
}

Stage::~Stage() {
}
