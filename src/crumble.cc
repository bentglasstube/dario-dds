#include "crumble.h"

#include "graphics.h"

Crumble::Crumble(Graphics& graphics, Crumble::Color color, unsigned int x, unsigned int y) :
  Sprite(graphics, "teeth", 0, 0, 16, 16),
  x(x), y(y), counter(0) {

  int sx = 0, sy = 0;

  switch (color) {
    case RED:          sx =  0; sy =  7; break;
    case YELLOW:       sx =  3; sy =  7; break;
    case ORANGE:       sx =  6; sy =  7; break;
    case WHITE:        sx =  9; sy =  7; break;
    case GREEN:        sx =  0; sy = 11; break;
    case BLUE:         sx =  3; sy = 11; break;
    case PURPLE:       sx =  6; sy = 11; break;
    case BLACK:        sx =  9; sy = 11; break;
    case TEETH:        sx =  8; sy =  3; break;
    case ROTTEN_TEETH: sx = 11; sy =  3; break;
  }

  rect.x = 16 * sx;
  rect.y = 16 * sy;
}

bool Crumble::update(unsigned int elapsed) {
  if (counter < 25 && counter + elapsed > 25) rect.x++;
  if (counter < 50 && counter + elapsed > 50) rect.x++;

  counter += elapsed;

  return counter < 75;
}

void Crumble::draw(Graphics& graphics, unsigned int x, unsigned int y) {
  Sprite::draw(graphics, this->x * 16 + x, this->y * 16 + y);
}
