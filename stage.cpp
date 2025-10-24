#include "stage.h"
#include "object.h"
#include "render_context.h"

Stage::Stage(vec2_t size) {
    size_ = size;
}

void Stage::tick(int64_t millisec) {
    for (auto object : objects_) {
        object->update(millisec);
        object->draw();
    }
}

bool Stage::init() {
    return true;
}

Stage::~Stage() {
}
