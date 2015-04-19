#include "main_screen.h"

#include "audio.h"
#include "input.h"
#include "text.h"

void MainScreen::init(Audio& audio, Graphics& graphics) {
  audio.play_music("rootcanal");

  game_grid = GameGrid();
  game_grid.generate(graphics);

  state = PLAYING;
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

    if (input.key_pressed(SDLK_LEFT) || input.key_pressed(SDLK_a)) {
      game_grid.move(-1);
    } else if (input.key_pressed(SDLK_RIGHT) || input.key_pressed(SDLK_d)) {
      game_grid.move(1);
    }

    if (input.key_pressed(SDLK_q)) {
      game_grid.rotate(-1);
    } else if (input.key_pressed(SDLK_UP) || input.key_pressed(SDLK_w) || input.key_pressed(SDLK_e)) {
      game_grid.rotate(1);
    }

    if (input.key_pressed(SDLK_DOWN) || input.key_pressed(SDLK_s)) {
      game_grid.drop(true);
    } else if (input.key_released(SDLK_DOWN) || input.key_released(SDLK_s)) {
      game_grid.drop(false);
    }

    switch (game_grid.update(audio, graphics, elapsed)) {
      case -1:
        state = GAME_OVER;
        break;

      case 1:
        state = VICTORY;
        break;
    }

  } else if (input.key_pressed(SDLK_r)) {

    game_grid = GameGrid();
    game_grid.generate(graphics);
    state = PLAYING;

  }

  return true;
}

void MainScreen::draw(Graphics& graphics) {
  game_grid.draw(graphics, 16, 16);

  switch (state) {

    case PAUSED:

      Text(graphics, "PAUSE").draw(graphics, 60, 136);
      break;

    case GAME_OVER:

      Text(graphics, "GAME OVER").draw(graphics, 44, 136);
      break;

    case VICTORY:

      Text(graphics, "YOU WIN").draw(graphics, 52, 136);
      break;

  }
}

Screen * MainScreen::next_screen() {
  // Always exit
  return NULL;
}
