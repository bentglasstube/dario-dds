#pragma once

#include "sprite.h"

class Graphics;

class ToothSprite : public Sprite {

  public:

    ToothSprite(Graphics& graphics);
    virtual ~ToothSprite() {}

    void draw(Graphics& graphics, int x, int y);

  private:

};
