#include "main_screen.h"

#include "graphics.h"
#include "sprite.h"

MainScreen::MainScreen(Graphics& graphics) {
  tooth_tl.reset(new Sprite(graphics, "teeth",  0,  0, 16, 16));
  tooth_tc.reset(new Sprite(graphics, "teeth", 16,  0, 16, 16));
  tooth_tr.reset(new Sprite(graphics, "teeth", 32,  0, 16, 16));
  tooth_ml.reset(new Sprite(graphics, "teeth",  0, 16, 16, 16));
  tooth_mc.reset(new Sprite(graphics, "teeth", 16, 16, 16, 16));
  tooth_mr.reset(new Sprite(graphics, "teeth", 32, 16, 16, 16));
}

bool MainScreen::update(unsigned int elapsed) {
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

  return true;
}

void MainScreen::draw(Graphics& graphics) {
  /* TODO draw all the game objects
   *
   * draw teeth
   * draw candy
   * draw UI
   *
   */

  for (int i = 0; i < 4; ++i) {
    tooth_tl->draw(graphics, 16 + 48 * i, 172);
    tooth_tc->draw(graphics, 32 + 48 * i, 172);
    tooth_tr->draw(graphics, 48 + 48 * i, 172);

    for (int j = 0; j < 2; ++j) {
      tooth_ml->draw(graphics, 16 + 48 * i, 188 + 16 * j);
      tooth_mc->draw(graphics, 32 + 48 * i, 188 + 16 * j);
      tooth_mr->draw(graphics, 48 + 48 * i, 188 + 16 * j);
    }
  }
}
