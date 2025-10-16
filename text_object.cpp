#include "text_object.h"
#include "render_context.h"

void TextObject::updateDirty()
{
    if(dirty_) {
        if(ttf_ != nullptr) {
            TTF_DestroyText(ttf_);
        }
        ttf_ = getRenderContext()->createText(text_.c_str(), size_);
        if(ttf_ != nullptr) {
            TTF_SetTextColor(ttf_, r, g, b, a);
        }
        dirty_ = false;
    }
}

void TextObject::draw() {
    updateDirty();
    TTF_DrawRendererText(ttf_, pos_.x, pos_.y);
}

void TextObject::setSize(int size) {
    size_ = size;
    dirty_ = true;
}

void TextObject::setText(const char* text) {
    text_ = text;
    dirty_ = true;
}

TextObject::~TextObject() {
    TTF_DestroyText(ttf_);
}
