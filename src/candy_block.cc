#include "candy_block.h"

#define RAND_COLOR (static_cast<Candy::Color>(rand() % 4))

CandyBlock::CandyBlock(Graphics& graphics, CandyBlock::Shape shape) {
  pieces[0][0].reset(new Candy(graphics, 1, RAND_COLOR));
  pieces[1][0].reset(new Candy(graphics, 8, RAND_COLOR));

  if (shape == THREE || shape == FOUR) {
    pieces[0][1].reset(new Candy(graphics, 4, RAND_COLOR));
    pieces[0][0]->set_connections(3);

    if (shape == FOUR) {
      pieces[1][1].reset(new Candy(graphics, 12, RAND_COLOR));
      pieces[1][0]->set_connections(10);
      pieces[0][1]->set_connections(5);
    }
  }
}

void CandyBlock::draw(Graphics& graphics, unsigned int x, unsigned int y) {
  for (int iy = 0; iy < 2; ++iy) {
    for (int ix = 0; ix < 2; ++ix) {
      if (pieces[iy][ix]) pieces[iy][ix]->draw(graphics, x + ix * 16, y + iy * 16);
    }
  }
}

void CandyBlock::rotate(bool clockwise) {
  boost::shared_ptr<Candy> temp = pieces[0][0];

  if (clockwise) {
    pieces[0][0] = pieces[1][0];
    pieces[1][0] = pieces[1][1];
    pieces[1][1] = pieces[0][1];
    pieces[0][1] = temp;
  } else {
    pieces[0][0] = pieces[0][1];
    pieces[0][1] = pieces[1][1];
    pieces[1][1] = pieces[1][0];
    pieces[1][0] = temp;
  }

  for (int iy = 0; iy < 2; ++iy) {
    for (int ix = 0; ix < 2; ++ix) {
      if (pieces[iy][ix]) pieces[iy][ix]->rotate(clockwise);
    }
  }
}

boost::shared_ptr<Candy> CandyBlock::piece_at(unsigned int x, unsigned int y) {
  return pieces[y][x];
}
