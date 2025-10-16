#include "stage.h"
#include "object.h"
#include "render_context.h"

Stage::Stage() 
{
}

void Stage::tick() {
    for (auto object : _objects) {
        object->draw();
    }
}

bool Stage::init() {
    return true;
}

Stage::~Stage() {
}
