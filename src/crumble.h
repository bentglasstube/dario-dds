#pragma once

#include "sprite.h"

class Graphics;

class Crumble : public Sprite {

  public:

    Crumble(Graphics& graphics, unsigned int x, unsigned int y);

    bool update(unsigned int elapsed);
    void draw(Graphics& graphics, unsigned int x, unsigned int y);

  private:

    unsigned int x, y, counter;
};
