#include "game_grid.h"

#include <boost/pointer_cast.hpp>

#include "audio.h"
#include "candy.h"
#include "graphics.h"
#include "tooth.h"

GameGrid::GameGrid(GameGrid::Difficulty difficulty) :
  move_counter(0), drop_counter(0), drop_speed(10),
  _move(0), _rotate(0), _drop(false),
  difficulty(difficulty) {}

void GameGrid::generate(Graphics& graphics) {
  for (int iy = 13; iy < 16; ++iy) {
    for (int ix = 0; ix < 8; ++ix) {
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

  // TODO scale auto-rotting with level
  for (int i = 0; i < 20; ++i) {
    int x = rand() % 8;
    int y = rand() % 2 + 13;

    damage_tooth(x, y);
  }

  // TODO spawn some candy on the teeth (difficulty scaled)

  if (!spawn_candy(graphics)) {
    fprintf(stderr, "Couldn't place initial candy, something went wrong\n");
  }
}

int GameGrid::update(Audio& audio, Graphics& graphics, unsigned int elapsed) {
  drop_counter += elapsed;
  move_counter += elapsed;

  if (active_piece && move_counter > 100) {
    move_counter = 0;
    if (_move != 0) {
      active_piece->slide(_move < 0);
      if (collision(active_piece)) {
        audio.play_sample("bump");
        active_piece->slide(_move > 0);
      }
      _move = 0;
    }


    if (_rotate != 0) {
      active_piece->rotate(_rotate > 0);
      if (collision(active_piece)) {
        audio.play_sample("bump");
        active_piece->rotate(_rotate < 0);
      }

      _rotate = 0;
    }
  }

  if (drop_counter > drop_threshold()) {
    drop_counter = 0;

    if (falling_pieces.empty()) {
      if (!active_piece) if (!spawn_candy(graphics)) return -1;

      active_piece->fall();
      if (collision(active_piece)) {
        audio.play_sample("bump");
        active_piece->fall(false);

        commit(active_piece);
        active_piece.reset();
      }
    } else {
      std::list<boost::shared_ptr<CandyBlock> >::iterator i = falling_pieces.begin();
      while (i != falling_pieces.end()) {
        (*i)->fall();
        if (collision(*i)) {
          (*i)->fall(false);
          commit(*i);
          i = falling_pieces.erase(i);
        } else {
          ++i;
        }
      }
    }

    process_matches(audio);
    if (winner()) return 1;
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

  for (std::list<boost::shared_ptr<CandyBlock> >::iterator i=falling_pieces.begin(); i != falling_pieces.end(); ++i) {
    (*i)->draw(graphics, x, y);
  }
}

boost::shared_ptr<GridPiece> GameGrid::piece(int x, int y) {
  if (x < 0 || x >= 8) return boost::shared_ptr<GridPiece>();
  if (y < 0 || y >= 16) return boost::shared_ptr<GridPiece>();
  return pieces[y][x];
}

boost::shared_ptr<Candy> GameGrid::candy_piece(int x, int y) {
  return boost::dynamic_pointer_cast<Candy>(piece(x, y));
}

boost::shared_ptr<Tooth> GameGrid::tooth_piece(int x, int y) {
  return boost::dynamic_pointer_cast<Tooth>(piece(x, y));
}

unsigned int GameGrid::drop_threshold() {
  return _drop || !active_piece ? 100 : 10000 / drop_speed;
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
  boost::shared_ptr<Candy> test = candy_piece(x, y);

  if (!test) return;

  boost::shared_ptr<Candy> empty = candy_piece(-1, -1);

  if (test->connected(8)) {
    boost::shared_ptr<Candy> above = candy_piece(x, y - 1);

    if (above->connected(4)) {

      boost::shared_ptr<Candy> above_left = candy_piece(x - 1, y - 1);

      boost::shared_ptr<CandyBlock> block(new CandyBlock(x - 1, y - 1, above_left, above, empty, test));
      falling_pieces.push_back(block);

      pieces[y - 1][x - 1].reset();

    } else {

      boost::shared_ptr<Candy> above_right = candy_piece((above->connected(2) ? x + 1 : -1), y - 1);
      boost::shared_ptr<Candy> right = candy_piece((test->connected(2) ? x + 1 : -1), y);

      boost::shared_ptr<CandyBlock> block(new CandyBlock(x, y - 1, above, above_right, test, right));
      falling_pieces.push_back(block);

      if (above_right) pieces[y - 1][x + 1].reset();
      if (right) pieces[y][x + 1].reset();

    }

    pieces[y - 1][x].reset();

  } else if (test->connected(2)) {

    boost::shared_ptr<Candy> right = candy_piece(x + 1, y);

    if (right->connected(8)) {
      boost::shared_ptr<Candy> above_right = candy_piece(x + 1, y - 1);

      boost::shared_ptr<CandyBlock> block(new CandyBlock(x, y - 1, empty, above_right, test, right));
      falling_pieces.push_back(block);

      pieces[y - 1][x + 1].reset();
    } else {
      boost::shared_ptr<CandyBlock> block(new CandyBlock(x, y, test, right, empty, empty));
      falling_pieces.push_back(block);
    }

    pieces[y][x + 1].reset();

  } else {
    boost::shared_ptr<CandyBlock> block(new CandyBlock(x, y, test, empty, empty, empty));
    falling_pieces.push_back(block);
  }

  pieces[y][x].reset();
}

void GameGrid::commit(boost::shared_ptr<CandyBlock> block) {
  for (int iy = 0; iy < 2; ++iy) {
    for (int ix = 0; ix < 2; ++ix) {
      if (block->piece_at(ix, iy)) pieces[block->get_y() + iy][block->get_x() + ix] = block->piece_at(ix, iy);
    }
  }
}

// TODO fix this bullshit code
int GameGrid::process_matches(Audio& audio) {
    std::list <Match> matches;

  for (int iy = 0; iy < 16; ++iy) {
    for (int ix = 0; ix < 8; ++ix) {
      boost::shared_ptr<Candy> start = candy_piece(ix, iy);
      if (!start) continue;

      if (ix < 5) {
        for (int j = ix; j <= 8; ++j) {
          boost::shared_ptr<Candy> test = candy_piece(j, iy);
          if (!test || test->color() != start->color()) {
            int length = j - ix;
            if (length >= 4) {
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
          boost::shared_ptr<Candy> test = candy_piece(ix, j);
          if (!test || test->color() != start->color()) {
            int length = j - iy;
            if (length >= 4) {
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

  int candy_count = 0;
  int tooth_count = 0;
  for (std::list<Match>::iterator i = matches.begin(); i != matches.end(); ++i) {
    if (remove_piece((*i).x, (*i).y)) {
      candy_count++;

      if (damage_tooth((*i).x, (*i).y - 1)) tooth_count++;
      if (damage_tooth((*i).x, (*i).y + 1)) tooth_count++;
      if (damage_tooth((*i).x - 1, (*i).y)) tooth_count++;
      if (damage_tooth((*i).x + 1, (*i).y)) tooth_count++;
    }
  }

  if (candy_count > 0) {
    for (int iy = 15; iy >= 0; --iy) {
      for (int ix = 0; ix < 8; ++ix) {
        if (piece(ix, iy)) release(ix, iy);
      }
    }
    if (tooth_count > 0) {
      audio.play_sample("break");
    } else {
      audio.play_sample("clear");
    }
  }

  return candy_count + tooth_count;
}

bool GameGrid::remove_piece(int x, int y) {
  if (piece(x, y)) {
    pieces[y][x].reset();
    if (piece(x - 1, y)) piece(x - 1, y)->break_connection(2);
    if (piece(x + 1, y)) piece(x + 1, y)->break_connection(4);
    if (piece(x, y - 1)) piece(x, y - 1)->break_connection(1);
    if (piece(x, y + 1)) piece(x, y + 1)->break_connection(8);

    return true;
  }

  return false;
}

bool GameGrid::damage_tooth(int x, int y) {
  boost::shared_ptr<Tooth> tooth = tooth_piece(x, y);
  if (tooth) {
    if (tooth->is_rotten()) {
      remove_piece(x, y);
      return true;
    } else {
      tooth->rot();
    }
  }

  return false;
}

bool GameGrid::winner() {

  switch (difficulty) {
    case HARD:
      // Destroy all the teeth
      for (int iy = 0; iy < 16; ++iy) {
        for (int ix = 0; ix < 8; ++ix) {
          if (tooth_piece(ix, iy)) return false;
        }
      }
      return true;

    case EASY:
      // Get to the gums only
      for (int ix = 0; ix < 8; ++ix) {
        if (!tooth_piece(ix, 15)) return true;
      }
      return false;

    default:
      // Endless ??
      return false;
  }
}
