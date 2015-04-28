#include "title_screen.h"

#include <boost/assign/list_of.hpp>

#include "audio.h"
#include "graphics.h"
#include "input.h"
#include "main_screen.h"
#include "settings_screen.h"

void TitleScreen::init(Audio& audio, Graphics& graphics) {
  audio.play_music("dario");

  choice = 0;
  backdrop.reset(new Backdrop(graphics, "title"));
  menu.reset(new Menu(graphics, boost::assign::list_of("Play")("Settings")("Quit")));
}

bool TitleScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {
  if (input.key_pressed(SDLK_ESCAPE) || input.key_pressed(SDLK_BACKQUOTE)) {
    choice = 2;
    return false;
  }

  if (input.key_pressed(SDLK_UP) || input.key_pressed(SDLK_w)) {
    choice = (choice + 2) % 3;
  }

  if (input.key_pressed(SDLK_DOWN) || input.key_pressed(SDLK_s)) {
    choice = (choice + 1) % 3;
  }

  if (input.key_pressed(SDLK_SPACE) || input.key_pressed(SDLK_RETURN)) {
    return false;
  }

  return true;
}

void TitleScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics);
  menu->draw(graphics, 400, choice);
}

Screen* TitleScreen::next_screen() {
  switch (choice) {
    case 0: return new MainScreen();
    case 1: return new SettingsScreen();
    default: return NULL;
  }
}
