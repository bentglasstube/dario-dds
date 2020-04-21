#pragma once

#include <memory>

#include "audio.h"
#include "graphics.h"

class Screen;

class Game {
  public:

    Game();
    ~Game();

    void start();
    void step();
    void loop();

  private:

    std::shared_ptr<Screen> screen;
    Graphics graphics;
    Audio audio;
    int last_update, last_frame;
};
