#include "main_screen.h"

#include <boost/format.hpp>

#include "audio.h"
#include "input.h"
#include "text.h"
#include "title_screen.h"

void MainScreen::init(Audio& audio, Graphics& graphics) {
  audio.play_music("rootcanal");

  game_grid = GameGrid();
  game_grid.generate(graphics, 1);

  state = PLAYING;
  score = 0;
  choice = 0;

  text.reset(new Text(graphics));
  box.reset(new Box(graphics));
  backdrop.reset(new Backdrop(graphics, "game"));
}

bool MainScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {

  if (input.key_pressed(SDLK_ESCAPE) || input.key_pressed(SDLK_BACKQUOTE)) {
    return false;
  }

  if (input.key_pressed(SDLK_SPACE) || input.key_pressed(SDLK_RETURN)) {
    if (state == PAUSED) {
      audio.play_sample("pause");
      state = PLAYING;
    } else if (state == PLAYING) {
      audio.play_sample("pause");
      state = PAUSED;
    }
  }

  if (state == PLAYING) {
    score += game_grid.update(input, audio, graphics, elapsed);

    int level = 1 + score / 1000;
    if (level > game_grid.get_level()) {
      audio.play_sample("levelup");
      game_grid.level_up();
    }

    if (game_grid.loser()) state = GAME_OVER;
    if (game_grid.winner()) state = VICTORY;

  } else if (input.key_pressed(SDLK_r)) {
    if (state != VICTORY) score = 0;

    game_grid = GameGrid();
    game_grid.generate(graphics, 1 + score / 1000);
    state = PLAYING;

  }

  return true;
}

void MainScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics);

  game_grid.draw(graphics, 256, 176);

  text->draw(graphics, 512, 64, "Score");
  text->draw(graphics, 512, 80, boost::str(boost::format("% 6u") % score));

  text->draw(graphics, 512, 112, "Level");
  text->draw(graphics, 560, 112, boost::str(boost::format("% 2u") % game_grid.get_level()));

  text->draw(graphics, 512, 128, "Next");
  game_grid.draw_next_piece(graphics, 576, 128);

  switch (state) {

    case PAUSED:

      text->draw(graphics, 320, 256, "Paused", true);
      break;

    case GAME_OVER:

      text->draw(graphics, 320, 256, "Game Over", true);
      break;

    case VICTORY:

      text->draw(graphics, 320, 256, "You Win!", true);
      break;

    case PLAYING:

      break;

  }
}

Screen * MainScreen::next_screen() { return new TitleScreen(); }
