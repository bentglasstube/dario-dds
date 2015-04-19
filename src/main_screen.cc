#include "main_screen.h"

#include "audio.h"
#include "input.h"
#include "text.h"

MainScreen::MainScreen(Graphics& graphics) : game_grid(GameGrid::EASY), state(PLAYING) {
  game_grid.generate(graphics);
}

bool MainScreen::process_input(Audio& audio, Input& input) {
  if (!Screen::process_input(audio, input)) {
    return false;
  }

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

  } else {

    if (input.key_pressed(SDLK_r)) state = RESTARTING;

  }

  return true;
}

bool MainScreen::update(Audio& audio, Graphics& graphics, unsigned int elapsed) {
  if (state == PLAYING) {
    int result = game_grid.update(audio, graphics, elapsed);

    switch (result) {
      case -1:
        state = GAME_OVER;
        break;

      case 1:
        state = VICTORY;
        break;
    }

  } else if (state == RESTARTING) {
    game_grid = GameGrid(GameGrid::EASY);
    game_grid.generate(graphics);

    state = PLAYING;
  }

  return true;
}

void MainScreen::draw(Graphics& graphics) {
  game_grid.draw(graphics, 16, 16);
  if (state == PAUSED) {
    Text text(graphics, "PAUSE");
    text.draw(graphics, 60, 136);
  } else if (state == GAME_OVER) {
    Text text(graphics, "GAME OVER");
    text.draw(graphics, 44, 136);
  } else if (state == VICTORY) {
    Text text(graphics, "YOU WIN");
    text.draw(graphics, 52, 136);
  }
}
