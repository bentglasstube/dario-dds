#include "crumble.h"

#include "graphics.h"

#define FRAME_LENGTH 25

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
  if (counter < FRAME_LENGTH  && counter + elapsed > FRAME_LENGTH ) rect.x += 16;
  if (counter < 2 * FRAME_LENGTH  && counter + elapsed > 2 * FRAME_LENGTH ) rect.x += 16;

  counter += elapsed;

  return counter < 3 * FRAME_LENGTH;
}

void Crumble::draw(Graphics& graphics, unsigned int x, unsigned int y) {
  Sprite::draw(graphics, this->x * 16 + x, this->y * 16 + y);
}
