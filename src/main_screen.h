#pragma once

#include "game_grid.h"
#include "screen.h"

class MainScreen : public Screen {
  public:
    MainScreen(Graphics& graphics);

    bool process_input(Audio& audio, Input& input);
    bool update(Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);

  private:

    enum State { PLAYING, PAUSED, GAME_OVER, VICTORY, RESTARTING };

    GameGrid game_grid;
    State state;

};
