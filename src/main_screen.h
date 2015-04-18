#pragma once

#include "game_grid.h"
#include "screen.h"

class Graphics;
class Sprite;

class MainScreen : public Screen {
  public:
    MainScreen(Graphics& graphics);

    bool update(unsigned int elapsed);
    void draw(Graphics& graphics);

  private:
    GameGrid game_grid;


};
