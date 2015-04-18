#include "grid_piece.h"

#include "graphics.h"

GridPiece::GridPiece(Graphics& graphics, unsigned int connections) : connections(connections) {
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

void GridPiece::set_connections(unsigned int connections) {
  this->connections = connections;
}

void GridPiece::rotate(bool clockwise) {
  switch (connections) {
    case  1: connections = clockwise ?  4 :  2; break;
    case  2: connections = clockwise ?  1 :  8; break;
    case  3: connections = clockwise ?  5 : 10; break;
    case  4: connections = clockwise ?  8 :  1; break;
    case  5: connections = clockwise ? 12 :  3; break;
    case  6: connections = 9;                   break;
    case  7: connections = clockwise ? 13 : 11; break;
    case  8: connections = clockwise ?  2 :  4; break;
    case  9: connections = 6;                   break;
    case 10: connections = clockwise ?  3 : 12; break;
    case 11: connections = clockwise ?  7 : 14; break;
    case 12: connections = clockwise ? 10 :  5; break;
    case 13: connections = clockwise ? 14 :  7; break;
    case 14: connections = clockwise ? 11 : 13; break;
  }
}
