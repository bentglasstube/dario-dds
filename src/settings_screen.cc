#include "settings_screen.h"

#include <boost/format.hpp>

#include "audio.h"
#include "input.h"
#include "title_screen.h"

void SettingsScreen::init(Audio& audio, Graphics& graphics) {
  audio.play_music("waitingroom");

  backdrop.reset(new Backdrop(graphics, "settings"));
  text.reset(new Text(graphics));
  tooth.reset(new Sprite(graphics, "ui", 0, 0, 16, 16));
  left.reset(new Sprite(graphics, "ui", 16, 32, 16, 16));
  right.reset(new Sprite(graphics, "ui", 32, 32, 16, 16));

  value[0] = value[1] = 10;
  value[2] = 0;
  value[3] = 1;

  min[0] = min[1] = min[2] = 0;
  min[3] = 1;

  max[0] = max[1] = 10;
  max[2] = 3;
  max[3] = 20;
}

bool SettingsScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {
  if (input.key_pressed(SDLK_ESCAPE) || input.key_pressed(SDLK_BACKQUOTE)) return false;

  if (input.key_pressed(SDLK_w) || input.key_pressed(SDLK_UP)) {
    choice = (choice + 4) % 5;
  }

  if (input.key_pressed(SDLK_s) || input.key_pressed(SDLK_DOWN)) {
    choice = (choice + 1) % 5;
  }

  if (input.key_pressed(SDLK_a) || input.key_pressed(SDLK_LEFT)) {
    change(false, audio);
  }

  if (input.key_pressed(SDLK_d) || input.key_pressed(SDLK_RIGHT)) {
    change(true, audio);
  }

  if (input.key_pressed(SDLK_SPACE) || input.key_pressed(SDLK_RETURN)) {
    if (choice == 4) return false;
  }

  return true;
}

void SettingsScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics);

  text->draw(graphics, 176, 240, "SFX Volume");
  text->draw(graphics, 176, 256, "Music Volume");
  text->draw(graphics, 176, 272, "Music Track");
  text->draw(graphics, 176, 288, "Starting Level");
  text->draw(graphics, 176, 304, "Back");

  std::string track;
  switch (value[2]) {
    case 0:
      track = "Random";
      break;

    case 1:
      track = "Root Canal";
      break;

    case 2:
      track = "Novacaine";
      break;

    case 3:
      track = "Fillings";
      break;
  }

  text->draw(graphics, 464, 240, boost::str(boost::format("%u") % value[0]), Text::RIGHT);
  text->draw(graphics, 464, 256, boost::str(boost::format("%u") % value[1]), Text::RIGHT);
  text->draw(graphics, 464, 272, track, Text::RIGHT);
  text->draw(graphics, 464, 288, boost::str(boost::format("%u") % value[3]), Text::RIGHT);

  int y = 16 * choice + 240;

  tooth->draw(graphics, 144, y);

  if (choice < 4) {
    int x = 464 - (choice == 2 ? 12 : 4) * 8;
    if (value[choice] > min[choice]) right->draw(graphics, x, y);
    if (value[choice] < max[choice]) left->draw(graphics, 464, y);
  }
}

Screen* SettingsScreen::next_screen() {
  return new TitleScreen();
}

void SettingsScreen::change(bool increase, Audio& audio) {
  if (choice > 3) return;

  if (increase) {
    if (value[choice] >= max[choice]) return;
    ++value[choice];
  } else {
    if (value[choice] <= min[choice]) return;
    --value[choice];
  }

  switch (choice) {
    case 0:
      audio.sfx_volume(value[choice]);
      audio.play_sample("bump");
      break;

    case 1:
      audio.music_volume(value[choice]);
      break;

    case 2:
      switch (value[choice]) {
        case 0:
          audio.play_music("waitingroom");
          break;

        case 1:
          audio.play_music("rootcanal");
          break;

        case 2:
          audio.play_music("novacaine");
          break;

        case 3:
          audio.play_music("fillings");
          break;
      }

      break;
  }
}
