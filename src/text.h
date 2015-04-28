#pragma once

#include <string>

#include "sprite.h"

class Text : public Sprite {

  public:

    enum Alignment { LEFT, CENTER, RIGHT };

    Text(Graphics& graphics);

    void draw(Graphics& graphics, unsigned int x, unsigned int y, std::string text, Alignment alignment=LEFT);

};

