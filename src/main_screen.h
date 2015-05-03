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

    void lost_focus() { if (state == PLAYING) state = PAUSED; }

    State state;
    unsigned int score, choice, starting_level;
    GameGrid game_grid;

    boost::scoped_ptr<Text> text;
    boost::scoped_ptr<Box> box;
    boost::scoped_ptr<Backdrop> backdrop;
};
