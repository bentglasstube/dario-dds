#include "candy.h"

Candy::Candy(Graphics& graphics, unsigned int connections, Candy::Color color) :
  GridPiece(graphics, connections),
  _color(color) {}

void Candy::get_source(SDL_Rect* rect) {
  unsigned int x = 2;
  unsigned int y = 2;

  switch (connections) {
    case  0: x = 2, y = 2; break;
    case  1: x = 2, y = 0; break;
    case  2: x = 0, y = 2; break;
    case  3: x = 0, y = 0; break;
    case  4: x = 1, y = 2; break;
    case  5: x = 1, y = 0; break;
    case  8: x = 2, y = 1; break;
    case 10: x = 0, y = 1; break;
    case 12: x = 1, y = 1; break;
  }

  switch (_color) {
    case RED:    x += 0; y += 0; break;
    case YELLOW: x += 3; y += 0; break;
    case ORANGE: x += 6; y += 0; break;
    case WHITE:  x += 9; y += 0; break;
    case GREEN:  x += 0; y += 4; break;
    case BLUE:   x += 3; y += 4; break;
    case PURPLE: x += 6; y += 4; break;
    case BLACK:  x += 9; y += 4; break;
  }

  rect->x = 16 * x;
  rect->y = 16 * y + 64;
  rect->w = 16;
  rect->h = 16;
}
