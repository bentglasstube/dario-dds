#pragma once

#include "grid_piece.h"

class Candy : public GridPiece {

  public:

    enum Color {
      GREEN  = 1,
      BLUE   = 2,
      YELLOW = 3,
      RED    = 4,
    };

    Candy(Graphics& graphics, Color color);

  private:

    void get_source(SDL_Rect* rect);

    Color color;
};
