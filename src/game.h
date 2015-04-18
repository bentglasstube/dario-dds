#pragma once

#include "graphics.h"

class Screen;

class Game {
  public:

    Game();
    ~Game();

    void loop();

  private:

    void draw(Graphics& graphics);
    Screen* current_screen;
};
