#pragma once

#include <boost/shared_ptr.hpp>

#include "grid_piece.h"

class Graphics;

class GameGrid {
  public:

    void generate(Graphics& graphics);
    int update(unsigned int elapsed);
    void draw(Graphics& graphics, unsigned int x, unsigned int y);

    // void spawn_candy();

  private:

    boost::shared_ptr<GridPiece> pieces[16][8];
};
