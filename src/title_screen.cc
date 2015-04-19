#include "title_screen.h"

#include "audio.h"
#include "graphics.h"
#include "input.h"
#include "main_screen.h"
#include "settings.h"
#include "text.h"

void TitleScreen::init(Audio& audio, Graphics& graphics) {
  audio.play_music("dario");

  choice = 0;
  backdrop.reset(new Backdrop(graphics, "title"));
  text.reset(new Text(graphics));
  tooth.reset(new Sprite(graphics, "ui", 0, 0, 16, 16));
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

  text->draw(graphics, 320, 400, "Play Game", true);
  text->draw(graphics, 320, 420, "Settings", true);
  text->draw(graphics, 320, 440, "Quit", true);

  tooth->draw(graphics, 256, 400 + choice * 20);
  tooth->draw(graphics, 368, 400 + choice * 20);
}

Screen* TitleScreen::next_screen() {
  switch (choice) {
    case 0: return new MainScreen();
    case 1: return new Settings();
    default: return NULL;
  }
}
