#pragma once

#include <boost/scoped_ptr.hpp>

#include "backdrop.h"
#include "box.h"
#include "game_grid.h"
#include "screen.h"
#include "text.h"

class MainScreen : public Screen {
  public:

    void init(Audio& audio, Graphics& graphics);
    bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);
    Screen* next_screen();

  private:

    enum State { PLAYING, PAUSED, GAME_OVER, VICTORY };

    GameGrid game_grid;
    State state;

    boost::scoped_ptr<Text> text;
    boost::scoped_ptr<Box> box;
    boost::scoped_ptr<Backdrop> backdrop;
};
