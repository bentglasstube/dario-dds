#include "game_grid.h"

#include "candy.h"
#include "graphics.h"
#include "tooth.h"

void GameGrid::generate(Graphics& graphics) {
  for (int iy = 10; iy < 14; ++iy) {
    for (int ix = 0; ix < 8; ++ix) {
      Candy::Color color = static_cast<Candy::Color>(rand() % 5);
      if (color == 0) continue;
      pieces[iy][ix].reset(new Candy(graphics, color));
    }
  }

  for (int iy = 14; iy < 16; ++iy) {
    for (int ix = 0; ix < 8; ++ix) {
      pieces[iy][ix].reset(new Tooth(graphics, rand() % 2 == 1));
    }
  }
}

int GameGrid::update(unsigned int elapsed) {
  /* TODO make the candy drop and shit
   *
   * update the drop timer on the falling candy
   * if falling candy settled
   *    check for loss condition
   *      game over son
   *    check for matches
   *      rot teeth
   *      drop things down
   *    start new candy falling
   *    generate next candy
   *
   */

  return 0;
}

void GameGrid::draw(Graphics& graphics, unsigned int x, unsigned int y) {
  for (int iy = 0; iy < 16; ++iy) {
    for (int ix = 0; ix < 8; ++ix) {
      if (pieces[iy][ix] != NULL) {
        pieces[iy][ix]->draw(graphics, x + 16 * ix, y + 16 * iy);
      }
    }
  }
}