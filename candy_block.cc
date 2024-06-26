#include "candy_block.h"

#define FLIP(A, B) (rand() % 2 == 0 ? (A) : (B))
#define RAND_COLOR static_cast<Candy::Color>((rand() % 2 ) * 4 + rand() % 2)

CandyBlock::CandyBlock(Graphics& graphics, CandyBlock::Shape shape, int x, int y) : x(x), y(y) {
  Candy::Color a = RAND_COLOR;
  Candy::Color b = RAND_COLOR;

  switch (shape) {

    case TWO:
      pieces[0][0].reset(new Candy(graphics, 1, a));
      pieces[1][0].reset(new Candy(graphics, 8, b));
      break;

    case THREE:
      pieces[0][0].reset(new Candy(graphics, 3, FLIP(a, b)));
      pieces[1][0].reset(new Candy(graphics, 8, a));
      pieces[0][1].reset(new Candy(graphics, 4, b));
      break;

    case FOUR:
      pieces[0][0].reset(new Candy(graphics,  3, a));
      pieces[1][0].reset(new Candy(graphics, 10, FLIP(a, b)));
      pieces[0][1].reset(new Candy(graphics,  5, FLIP(a, b)));
      pieces[1][1].reset(new Candy(graphics, 12, b));
      break;
  }

  int spin = rand() % 4;
  for (int i = 0; i < spin; ++i) {
    rotate();
  }
}

CandyBlock::CandyBlock(
    int x, int y,
    std::shared_ptr<Candy> a, std::shared_ptr<Candy> b,
    std::shared_ptr<Candy> c, std::shared_ptr<Candy> d) : x(x), y(y) {
  pieces[0][0] = a;
  pieces[0][1] = b;
  pieces[1][0] = c;
  pieces[1][1] = d;
}

void CandyBlock::draw(Graphics& graphics, int x, int y) {
  for (int iy = 0; iy < 2; ++iy) {
    for (int ix = 0; ix < 2; ++ix) {
      if (pieces[iy][ix]) pieces[iy][ix]->draw(graphics, x + (this->x + ix) * 16, y + (this->y + iy) * 16);
    }
  }
}

void CandyBlock::rotate(bool clockwise) {
  std::shared_ptr<Candy> temp = pieces[0][0];

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

  // Slide the piece back to the top left if possible
  if (!pieces[0][0]) {
    if (!pieces[0][1]) {
      pieces[0][0] = pieces[1][0];
      pieces[0][1] = pieces[1][1];
      pieces[1][0].reset();
      pieces[1][1].reset();
    } else if (!pieces[1][0]) {
      pieces[0][0] = pieces[0][1];
      pieces[1][0] = pieces[1][1];
      pieces[0][1].reset();
      pieces[1][1].reset();
    }
  }
}

std::shared_ptr<Candy> CandyBlock::piece_at(int x, int y) {
  return pieces[y][x];
}
