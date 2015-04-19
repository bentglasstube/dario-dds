#include "settings.h"

#include "audio.h"
#include "title_screen.h"

void Settings::init(Audio& audio, Graphics& graphics) {
  audio.play_music("waitingroom");
}

bool Settings::update(Input& input, Audio& audio, Graphics& graphics) {

}

void Settings::draw(Graphics& graphics) {

}

Screen* Settings::next_screen() {
  return new TitleScreen();
}
