#pragma once

#include <memory>

#include "audio.h"
#include "graphics.h"
#include "input.h"

class Screen;

class Game {
  public:

    Game();
    ~Game();

    void start();
    void step();
    void loop();

  private:

    std::unique_ptr<Screen> screen;
    std::unique_ptr<Graphics> graphics;
    Audio audio;
    Input input;
    int last_update;
};
