#pragma once

#include <boost/shared_ptr.hpp>

#include "candy.h"

class CandyBlock {
  public:

    enum Shape { TWO, THREE, FOUR };

    CandyBlock(Graphics& graphics, Shape shape, int x, int y);
    CandyBlock(int x, int y, boost::shared_ptr<Candy> a, boost::shared_ptr<Candy> b, boost::shared_ptr<Candy> c, boost::shared_ptr<Candy> d);

    void draw(Graphics& graphics, int x, int y);

    void rotate(bool clockwise=true);
    void slide(bool left=true) { x += left ? -1 : 1; }
    void fall(bool down=true) { y += down ? 1 : -1; }
    int get_x() { return x; }
    int get_y() { return y; }

    boost::shared_ptr<Candy> piece_at(int x, int y);

  private:
    boost::shared_ptr<Candy> pieces[2][2];
    int x, y;
};
