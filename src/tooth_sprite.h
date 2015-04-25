#pragma once

#include "sprite.h"

class Graphics;

class ToothSprite : public Sprite {

  public:

    ToothSprite(Graphics& graphics);

    void draw(Graphics& graphics, unsigned int x, unsigned int y);

  private:

};
