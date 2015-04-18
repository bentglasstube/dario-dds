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

  /* TODO handle other input
   *
   * left/a  - move piece left
   * right/b - move piece right
   * down/s  - fast drop
   * up/w/q  - rotate clockwise
   * e       - rotate counterclockwise
   * space   - pause
   */

  return true;
}

bool MainScreen::update(unsigned int elapsed) {
  game_grid.update(elapsed);

  return true;
}

void MainScreen::draw(Graphics& graphics) {
  game_grid.draw(graphics, 16, 16);

  // TODO draw ui
}
