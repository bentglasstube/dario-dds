#include "settings.h"

#include "audio.h"
#include "input.h"
#include "title_screen.h"

void Settings::init(Audio& audio, Graphics& graphics) {
  audio.play_music("waitingroom");

  backdrop.reset(new Backdrop(graphics, "settings"));
  text.reset(new Text(graphics));
}

bool Settings::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {
  if (input.key_pressed(SDLK_ESCAPE) || input.key_pressed(SDLK_BACKQUOTE)) return false;

  return true;
}

void Settings::draw(Graphics& graphics) {
  backdrop->draw(graphics);

  text->draw(graphics, 320, 240, "Sorry no settings yet", true);
  text->draw(graphics, 320, 260, "ESC to go back", true);
}

Screen* Settings::next_screen() {
  return new TitleScreen();
}
