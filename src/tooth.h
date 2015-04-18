#pragma once

#include "grid_piece.h"

class Tooth : public GridPiece {
  public:

    Tooth(Graphics& graphics, unsigned int connections, bool rotten);

  private:

    void get_source(SDL_Rect* rect);

    bool rotten;
};
