#pragma once

#include "grid_piece.h"

class Tooth : public GridPiece {
  public:

    Tooth(Graphics& graphics, int connections, bool rotten);

    bool is_rotten() { return rotten; }
    void rot() { rotten = true; }

  private:

    void get_source(SDL_Rect* rect);

    bool rotten;
};
