#include "tooth.h"

Tooth::Tooth(Graphics& graphics, unsigned int connections, bool rotten) :
  GridPiece(graphics, connections),
  rotten(rotten) {}

void Tooth::get_source(SDL_Rect* rect) {
  unsigned int x = 0;
  unsigned int y = 0;

  switch (connections) {
    case  0: x = 4, y = 4; break;
    case  1: x = 4, y = 0; break;
    case  2: x = 0, y = 4; break;
    case  3: x = 0, y = 0; break;
    case  4: x = 2, y = 4; break;
    case  5: x = 2, y = 0; break;
    case  6: x = 1, y = 4; break;
    case  7: x = 1, y = 0; break;
    case  8: x = 4, y = 2; break;
    case  9: x = 4, y = 1; break;
    case 10: x = 0, y = 2; break;
    case 11: x = 0, y = 1; break;
    case 12: x = 2, y = 2; break;
    case 13: x = 2, y = 1; break;
    case 14: x = 1, y = 2; break;
    case 15: x = 1, y = 1; break;
  }

  if (rotten) x += 4;

  rect->x = 16 * x;
  rect->y = 16 * y;
  rect->w = 16;
  rect->h = 16;
}
