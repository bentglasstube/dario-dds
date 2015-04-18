#pragma once

#include "screen.h"

class Graphics;

class MainScreen : public Screen {
  public:
    MainScreen(Graphics& graphics);

    bool update(unsigned int elapsed);
    void draw(Graphics& graphics);

  private:

    // TODO save all the game objects
};
