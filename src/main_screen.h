#pragma once

#include "game_grid.h"
#include "screen.h"

class MainScreen : public Screen {
  public:
    MainScreen(Graphics& graphics);

    bool process_input(Input& input);
    bool update(Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);

  private:

    enum State { PLAYING, PAUSED, GAME_OVER };

    GameGrid game_grid;
    State state;

};
