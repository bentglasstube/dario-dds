#pragma once

#include <string>

#include "sprite.h"

class Text : public Sprite {

  public:

    Text(Graphics& graphics);

    void draw(Graphics& graphics, unsigned int x, unsigned int y, std::string text, bool centered=false);

};

