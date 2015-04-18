#pragma once

#include "game_grid.h"
#include "screen.h"

class MainScreen : public Screen {
  public:
    MainScreen(Graphics& graphics);

    bool process_input(Input& input);
    bool update(unsigned int elapsed);
    void draw(Graphics& graphics);

  private:

    GameGrid game_grid;

};
