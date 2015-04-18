#pragma once

#include <string>

#include "sprite.h"

class Text : public Sprite {

  public:

    Text(Graphics& graphics, std::string text);

    void draw(Graphics& graphics, unsigned int x, unsigned int y);

  private:

    std::string text;
};

