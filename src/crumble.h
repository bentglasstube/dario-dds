#pragma once

#include "sprite.h"

class Graphics;

class Crumble : public Sprite {

  public:

    Crumble(Graphics& graphics, int x, int y);

    bool update(int elapsed);
    void draw(Graphics& graphics, int x, int y);

  private:

    int x, y, counter;
};
