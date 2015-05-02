#include "main_screen.h"

#include <boost/assign/list_of.hpp>
#include <boost/format.hpp>

#include "audio.h"
#include "input.h"
#include "menu.h"
#include "settings.h"
#include "text.h"
#include "title_screen.h"

namespace {
  const unsigned int POINTS_PER_LEVEL = 1000;
}

void MainScreen::init(Audio& audio, Graphics& graphics) {
  // TODO improve random track play
  unsigned int track = Settings::get_instance().music_track;
  if (track == 0) track = 1 + rand() % 3;

  switch (track) {
    case 1: audio.play_music("rootcanal"); break;
    case 2: audio.play_music("novacaine"); break;
    case 3: audio.play_music("fillings");  break;
  }

  audio.sfx_volume(Settings::get_instance().sfx_volume);
  audio.music_volume(Settings::get_instance().music_volume);

  state = PLAYING;
  score = 0;
  choice = 0;
  starting_level = Settings::get_instance().starting_level;

  game_grid = GameGrid();
  game_grid.generate(graphics, starting_level);

  text.reset(new Text(graphics));
  box.reset(new Box(graphics));
  backdrop.reset(new Backdrop(graphics, "game"));
}

bool MainScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {

  if (input.key_pressed(Input::BACK)) {
    return false;
  }

  if (state == PLAYING) {
    score += game_grid.update(input, audio, graphics, elapsed);

    unsigned int level = 1 + score / POINTS_PER_LEVEL;
    if (level > game_grid.get_level()) {
      audio.play_sample("levelup");
      game_grid.level_up();
    }

    if (input.key_pressed(Input::ACCEPT)) {
      audio.play_sample("paused");
      state = PAUSED;
    }

    if (game_grid.loser()) state = GAME_OVER;
    if (game_grid.winner()) state = VICTORY;

  } else {
    // these are the same because there are always only 2 options
    if (input.key_pressed(Input::UP)) {
      choice = (choice + 1) % 2;
    } else if (input.key_pressed(Input::DOWN)) {
      choice = (choice + 1) % 2;
    }

    if (input.key_pressed(Input::ACCEPT)) {
      if (choice == 1) return false;

      if (state == PAUSED) {
        audio.play_sample("paused");
      } else {

        // Restart and Continue are the same thing really, but we need to reset
        // the score if restarting
        if (state == GAME_OVER) score = 0;
        game_grid.generate(graphics, starting_level + score / POINTS_PER_LEVEL);
      }

      state = PLAYING;
    }
  }

  return true;
}

void MainScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics);

  game_grid.draw(graphics, 256, 176);

  text->draw(graphics, 512, 112, "Score");
  text->draw(graphics, 560, 112, boost::str(boost::format("%u") % score));

  text->draw(graphics, 512, 96, "Level");
  text->draw(graphics, 560, 96, boost::str(boost::format("%u") % game_grid.get_level()));

  text->draw(graphics, 512, 128, "Next");
  game_grid.draw_next_piece(graphics, 560, 128);

  std::string title;
  std::list<std::string> options;

  switch (state) {

    case PAUSED:

      title = "Paused";
      options = boost::assign::list_of("Resume")("Quit");
      break;

    case GAME_OVER:

      title = "Game Over";
      options = boost::assign::list_of("Restart")("Quit");
      break;

    case VICTORY:

      title = "You Win!";
      options = boost::assign::list_of("Continue")("Quit");
      break;

    case PLAYING: break;

  }

  if (state != PLAYING) {
    Box box(graphics);
    box.draw(graphics, 224, 224, 192, 128);

    text->draw(graphics, 320, 256, title, Text::CENTER);

    Menu menu(graphics, options);
    menu.draw(graphics, 288, choice);
  }
}

Screen * MainScreen::next_screen() { return new TitleScreen(); }
