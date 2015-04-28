#include "crumble.h"

#include "graphics.h"

#define FRAME_LENGTH 25
#define FRAME_COUNT  6

Crumble::Crumble(Graphics& graphics, unsigned int x, unsigned int y) :
  Sprite(graphics, "teeth", 240, 0, 16, 16),
  x(x * 16), y(y * 16), counter(0) {}

bool Crumble::update(unsigned int elapsed) {
  for (int i = 1;  i < FRAME_COUNT; ++i) {
    if (counter < i * FRAME_LENGTH  && counter + elapsed > i * FRAME_LENGTH ) {
      rect.y += 16;
      y -= 4;
    }
  }

  counter += elapsed;

  return counter < FRAME_COUNT * FRAME_LENGTH;
}

void Crumble::draw(Graphics& graphics, unsigned int x, unsigned int y) {
  Sprite::draw(graphics, this->x + x, this->y + y);
}
