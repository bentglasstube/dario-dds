#include "grid_piece.h"

#include "graphics.h"

GridPiece::GridPiece(Graphics& graphics) : connections(0) {
  texture = graphics.load_image("teeth", true);
}

void GridPiece::draw(Graphics& graphics, unsigned int x, unsigned int y) {
  SDL_Rect source, dest;

  get_source(&source);

  dest.x = x;
  dest.y = y;
  dest.w = 16;
  dest.h = 16;

  graphics.blit(texture, &source, &dest);
}
