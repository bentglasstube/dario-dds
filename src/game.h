#pragma once

#include <boost/shared_ptr.hpp>

class Screen;
class Graphics;

class Game {
  public:

    Game();
    ~Game();

    void loop();

  private:

    boost::shared_ptr<Screen> screen;
};
