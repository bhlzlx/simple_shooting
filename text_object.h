#pragma once
#include "object.h"
#include <string>

struct TTF_Text;

class TextObject : public Object {
    std::string                 text_;
    int                         size_;
    TTF_Text*                   ttf_;
    uint8_t                     r,g,b,a;
    bool                        dirty_;
public:
    TextObject(std::string txt, int size) 
        : text_(txt), size_(size), ttf_(nullptr), dirty_(true), r(255), g(255), b(255), a(255) {}

    void updateDirty();
    void setText(const char* text);
    void setSize(int size);
    virtual void draw() override;
    virtual ~TextObject();
};