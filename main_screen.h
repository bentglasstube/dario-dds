#pragma once

#include <memory>

#include "backdrop.h"
#include "box.h"
#include "face.h"
#include "game_grid.h"
#include "screen.h"
#include "text.h"

class MainScreen : public Screen {
  public:

    void init(Graphics& graphics);
    bool update(Input& input, Audio& audio, Graphics& graphics, int elapsed);
    void draw(Graphics& graphics);
    Screen* next_screen();
    std::string get_music_track();

  private:

    enum State { PLAYING, PAUSED, GAME_OVER, VICTORY };

    void lost_focus() { if (state == PLAYING) state = PAUSED; }

    State state;
    int score, choice, starting_level;
    std::unique_ptr<Face> face;
    GameGrid game_grid;

    std::unique_ptr<Text> text;
    std::unique_ptr<Box> box;
    std::unique_ptr<Backdrop> backdrop;
};
