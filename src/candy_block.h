#pragma once

#include <boost/shared_ptr.hpp>

#include "candy.h"

class CandyBlock {
  public:

    enum Shape { TWO, THREE, FOUR };

    CandyBlock(Graphics& graphics, Shape shape);

    void draw(Graphics& graphics, unsigned int x, unsigned int y);
    void rotate(bool clockwise=true);
    boost::shared_ptr<Candy> piece_at(unsigned int x, unsigned int y);

  private:
    boost::shared_ptr<Candy> pieces[2][2];
};
