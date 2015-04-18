#include "game_grid.h"

#include <boost/pointer_cast.hpp>

#include "candy.h"
#include "graphics.h"
#include "tooth.h"

GameGrid::GameGrid() :
  move_counter(0), drop_counter(0), drop_speed(10),
  _move(0), _rotate(0), _drop(false) {}

void GameGrid::generate(Graphics& graphics) {
  for (int iy = 13; iy < 16; ++iy) {
    for (int ix = 0; ix < 8; ++ix) {
      // TODO scale rotten % with difficulty
      int connections = 15;

      switch (ix) {
        case 0:
        case 4:
          connections &= ~4;
          break;
        case 3:
        case 7:
          connections &= ~2;
          break;
      }

      if (iy == 13) connections &= ~8;

      pieces[iy][ix].reset(new Tooth(graphics, connections, false));
    }
  }

  // TODO spawn some candy on the teeth (difficulty scaled)

  if (!spawn_candy(graphics)) {
    fprintf(stderr, "Couldn't place initial candy, something went wrong\n");
  }
}

int GameGrid::update(Graphics& graphics, unsigned int elapsed) {
  drop_counter += elapsed;
  move_counter += elapsed;

  if (falling_pieces.empty() && move_counter > 100) {
    move_counter = 0;
    if (_move != 0) {
      active_piece->slide(_move < 0);
      if (collision(active_piece)) {
        // TODO play bump sound
        active_piece->slide(_move > 0);
      }
      _move = 0;
    }


    if (_rotate != 0) {
      active_piece->rotate(_rotate > 0);
      if (collision(active_piece)) {
        // TODO play bump sound
        active_piece->rotate(_rotate < 0);
      }

      _rotate = 0;
    }
  }

  if (drop_counter > drop_threshold()) {
    drop_counter = 0;

    if (falling_pieces.empty()) {
      fprintf(stderr, "Active piece processing\n");
      active_piece->fall();
      if (collision(active_piece)) {
        // TODO play bump sound
        active_piece->fall(false);
        fprintf(stderr, "Piece landed, committing\n");

        commit(active_piece);
        process_matches();

        if (!spawn_candy(graphics)) {
          fprintf(stderr, "Nowhere to place candy, game over\n");
          return -1;
        }
      }
    } else {
      fprintf(stderr, "Falling piece processing\n");
      std::list<boost::shared_ptr<CandyBlock> >::iterator i = falling_pieces.begin();
      while (i != falling_pieces.end()) {
        bool active = true;

        ++i;
      }
    }
  }

  return 0;
}

void GameGrid::draw(Graphics& graphics, unsigned int x, unsigned int y) {
  for (int iy = 0; iy < 16; ++iy) {
    for (int ix = 0; ix < 8; ++ix) {
      if (pieces[iy][ix]) pieces[iy][ix]->draw(graphics, x + 16 * ix, y + 16 * iy);
    }
  }

  if (active_piece) active_piece->draw(graphics, x, y);
}

boost::shared_ptr<GridPiece> GameGrid::piece(int x, int y) {
  if (x < 0 || x >= 8) return boost::shared_ptr<GridPiece>();
  if (y < 0 || y >= 16) return boost::shared_ptr<GridPiece>();
  return pieces[y][x];
}

unsigned int GameGrid::drop_threshold() {
  return _drop ? 100 : 10000 / drop_speed;
}

bool GameGrid::spawn_candy(Graphics& graphics) {
  CandyBlock::Shape shape;
  int picker = rand() % 100;

  // stop fast drop for new pieces
  _drop = false;

  if (picker < 50)      { shape = CandyBlock::TWO;   }
  else if (picker < 85) { shape = CandyBlock::THREE; }
  else                  { shape = CandyBlock::FOUR;  }

  active_piece.reset(new CandyBlock(graphics, shape, 3, 0));

  for (int i = 0; i < 3; ++i) {
    if (!collision(active_piece)) return true;
    active_piece->rotate();
  }

  active_piece.reset();

  return false;
}

bool GameGrid::collision(boost::shared_ptr<CandyBlock> block) {
  if (!block) return false;

  for (int iy = 0; iy < 2; ++iy) {
    for (int ix = 0; ix < 2; ++ix) {
      if (block->piece_at(ix, iy)) {
        if (block->get_x() + ix < 0 || block->get_x() + ix >= 8) return true;
        if (block->get_y() + iy < 0 || block->get_y() + iy >= 16) return true;
        if (pieces[block->get_y() + iy][block->get_x() + ix]) return true;
      }
    }
  }

  return false;
}

void GameGrid::release(int x, int y) {
  fprintf(stderr, "Releasing block at %u, %u", x, y);

  boost::shared_ptr<Candy> a = boost::dynamic_pointer_cast<Candy>(piece(x + 0, y + 0));
  boost::shared_ptr<Candy> b = boost::dynamic_pointer_cast<Candy>(piece(-1, -1));
  boost::shared_ptr<Candy> c = boost::dynamic_pointer_cast<Candy>(piece(-1, -1));
  boost::shared_ptr<Candy> d = boost::dynamic_pointer_cast<Candy>(piece(-1, -1));
  /* TODO sort this shit out
  boost::shared_ptr<Candy> b = boost::dynamic_pointer_cast<Candy>(piece(x + 1, y + 0));
  boost::shared_ptr<Candy> c = boost::dynamic_pointer_cast<Candy>(piece(x + 0, y + 1));
  boost::shared_ptr<Candy> d = boost::dynamic_pointer_cast<Candy>(piece(x + 1, y + 1));
  */

  if (!a) return;

  boost::shared_ptr<CandyBlock> block(new CandyBlock(x, y, a, b, c, d));
  falling_pieces.push_back(block);

  if (a) pieces[y + 0][x + 0].reset();
  if (b) pieces[y + 0][x + 1].reset();
  if (c) pieces[y + 1][x + 0].reset();
  if (d) pieces[y + 1][x + 1].reset();
}

void GameGrid::commit(boost::shared_ptr<CandyBlock> block) {
  for (int iy = 0; iy < 2; ++iy) {
    for (int ix = 0; ix < 2; ++ix) {
      if (block->piece_at(ix, iy)) pieces[block->get_y() + iy][block->get_x() + ix] = block->piece_at(ix, iy);
    }
  }
}

// TODO fix this bullshit code
int GameGrid::process_matches() {
    std::list <Match> matches;

  for (int iy = 0; iy < 16; ++iy) {
    for (int ix = 0; ix < 8; ++ix) {
      boost::shared_ptr<Candy> start = boost::dynamic_pointer_cast<Candy>(piece(ix, iy));
      if (!start) continue;

      if (ix < 5) {
        for (int j = ix; j <= 8; ++j) {
          boost::shared_ptr<Candy> test = boost::dynamic_pointer_cast<Candy>(piece(j, iy));
          if (!test || test->color() != start->color()) {
            int length = j - ix;
            if (length >= 4) {
              fprintf(stderr, "Found horizontal match %u long starting at %u, %u\n", length, ix, iy);
              for (int k = ix; k < j; ++k) {
                matches.push_back(Match(k, iy));
              }
            }
            break;
          }
        }
      }

      if (iy < 13) {
        for (int j = iy; j <= 16; ++j) {
          boost::shared_ptr<Candy> test = boost::dynamic_pointer_cast<Candy>(piece(ix, j));
          if (!test || test->color() != start->color()) {
            int length = j - iy;
            if (length >= 4) {
              fprintf(stderr, "Found vertical match %u long starting at %u, %u\n", length, ix, iy);
              for (int k = iy; k < j; ++k) {
                matches.push_back(Match(ix, k));
              }
            }
            break;
          }
        }
      }

    }
  }

  for (std::list<Match>::iterator i = matches.begin(); i != matches.end(); ++i) {
    remove_piece((*i).x, (*i).y);
  }

  // TODO fall down bitches

  for (int iy = 0; iy < 16; ++iy) {
    for (int ix = 0; ix < 8; ++ix) {
      // if (piece(ix, iy)) release(ix, iy);
    }
  }

  return 0;
}

void GameGrid::remove_piece(int x, int y) {
  if (x < 0 || x >= 8) return;
  if (y < 0 || y >= 16) return;

  if (piece(x, y)) {
    pieces[y][x].reset();
    if (piece(x - 1, y)) piece(x - 1, y)->break_connection(2);
    if (piece(x + 1, y)) piece(x + 1, y)->break_connection(4);
    if (piece(x, y - 1)) piece(x, y - 1)->break_connection(1);
    if (piece(x, y + 1)) piece(x, y + 1)->break_connection(8);
  }
}
