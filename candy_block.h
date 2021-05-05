#pragma once

#include <memory>

#include "candy.h"

class CandyBlock {
  public:

    enum Shape { TWO, THREE, FOUR };

    CandyBlock(Graphics& graphics, Shape shape, int x, int y);
    CandyBlock(int x, int y, std::shared_ptr<Candy> a, std::shared_ptr<Candy> b, std::shared_ptr<Candy> c, std::shared_ptr<Candy> d);

    void draw(Graphics& graphics, int x, int y);

    void rotate(bool clockwise=true);
    void slide(bool left=true) { x += left ? -1 : 1; }
    void fall(bool down=true) { y += down ? 1 : -1; }
    int get_x() { return x; }
    int get_y() { return y; }

    std::shared_ptr<Candy> piece_at(int x, int y);

  private:
    std::shared_ptr<Candy> pieces[2][2];
    int x, y;
};
