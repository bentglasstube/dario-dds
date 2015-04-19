#include "title_screen.h"

#include "audio.h"
#include "graphics.h"
#include "input.h"
#include "main_screen.h"
#include "text.h"

void TitleScreen::init(Audio& audio, Graphics& graphics) {
  audio.play_music("dario");
  counter = 0;
  backdrop.reset(new Backdrop(graphics, "title"));
  text.reset(new Text(graphics));
}

bool TitleScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {
  if (input.any_key_pressed()) return false;

  counter = (counter + elapsed) % 1000;

  return true;
}

void TitleScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics);
  if (counter < 500) text->draw(graphics, 320, 392, "Press any key", true);
}

Screen* TitleScreen::next_screen() { return new MainScreen(); }
