#include "floating_text.h"

#define DURATION 1000
#define DISTANCE 32

bool FloatingText::update(unsigned int elapsed) {
  counter += elapsed;
  return counter < DURATION;
}

void FloatingText::draw(Graphics& graphics, unsigned int x, unsigned int y) {
  Text::draw(graphics, x + this->x, y + this->y - DISTANCE * counter / DURATION, text);
}
