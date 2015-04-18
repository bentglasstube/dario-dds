#include "candy.h"

Candy::Candy(Graphics& graphics, Candy::Color color) : GridPiece(graphics), color(color) {}

void Candy::get_source(SDL_Rect* rect) {
  unsigned int x = 0;
  unsigned int y = 0;

  switch (connections) {
    case  1: x = 2; y = 1; break;
    case  2: x = 2; y = 0; break;
    case  3: x = 0; y = 0; break;
    case  4: x = 3; y = 0; break;
    case  5: x = 1; y = 0; break;
    case  8: x = 3; y = 1; break;
    case 10: x = 0; y = 1; break;
    case 12: x = 1; y = 1; break;
  }

  switch (color) {
    case RED:    x += 4; y += 2; break;
    case BLUE:   x += 4; y += 0; break;
    case GREEN:  x += 0; y += 0; break;
    case YELLOW: x += 0; y += 2; break;
  }

  rect->x = 16 * x;
  rect->y = 16 * y + 64;
  rect->w = 16;
  rect->h = 16;
}
