#include "main_screen.h"

#include "graphics.h"
#include "sprite.h"

MainScreen::MainScreen(Graphics& graphics) : game_grid() {
  game_grid.generate(graphics);
}

bool MainScreen::update(unsigned int elapsed) {
  game_grid.update(elapsed);

  return true;
}

void MainScreen::draw(Graphics& graphics) {
  game_grid.draw(graphics, 16, 16);

  // TODO draw ui
}
