#include "tooth.h"

Tooth::Tooth(Graphics& graphics, unsigned int connections, bool rotten) :
  GridPiece(graphics, connections),
  rotten(rotten) {}

void Tooth::get_source(SDL_Rect* rect) {
  unsigned int x = (connections & 3) + (rotten ? 4 : 0);
  unsigned int y = connections >> 2;

  rect->x = 16 * x;
  rect->y = 16 * y;
  rect->w = 16;
  rect->h = 16;
}
