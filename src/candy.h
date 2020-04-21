#pragma once

#include "grid_piece.h"

class Candy : public GridPiece {

  public:

    enum Color {
      RED, YELLOW, ORANGE, WHITE,
      GREEN, BLUE, PURPLE, BLACK
    };

    Candy(Graphics& graphics, int connections, Color color);
    virtual ~Candy() {}

    Color color() { return _color; }

  private:

    void get_source(SDL_Rect* rect);

    Color _color;
};
