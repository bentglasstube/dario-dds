#pragma once

#include <memory>

class Screen;
class Graphics;

class Game {
  public:

    Game();
    ~Game();

    void loop();

  private:

    std::shared_ptr<Screen> screen;
};
