#include "main_screen.h"

#include "input.h"

MainScreen::MainScreen(Graphics& graphics) : game_grid() {
  game_grid.generate(graphics);
}

bool MainScreen::process_input(Input& input) {
  if (!Screen::process_input(input)) {
    return false;
  }

  if (input.key_pressed(SDLK_ESCAPE)) {
    return false;
  }

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

  return true;
}

bool MainScreen::update(Graphics& graphics, unsigned int elapsed) {
  int result = game_grid.update(graphics, elapsed);

  return result >= 0;
}

void MainScreen::draw(Graphics& graphics) {
  game_grid.draw(graphics, 16, 16);

  // TODO draw ui
}
