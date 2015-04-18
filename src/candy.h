#pragma once

#include "grid_piece.h"

class Candy : public GridPiece {

  public:

    enum Color { RED, BLUE, GREEN, YELLOW };

    Candy(Graphics& graphics, unsigned int connections, Color color);

  private:

    void get_source(SDL_Rect* rect);

    Color color;
};
