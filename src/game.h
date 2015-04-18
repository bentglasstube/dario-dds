#pragma once

#include "graphics.h"

class Game {
  public:

    Game();
    ~Game();

    void loop();

  private:

    void draw(Graphics& graphics);
};
