#include "game_grid.h"

#include <boost/pointer_cast.hpp>

#include "audio.h"
#include "candy.h"
#include "graphics.h"
#include "input.h"
#include "tooth.h"

void GameGrid::generate(Graphics& graphics, unsigned int starting_level) {
  level = starting_level;

  falling_pieces.clear();

  for (int iy = 0; iy < 16; ++iy) {
    for (int ix = 0; ix < 8; ++ix) {

      if (iy < 13) {
        pieces[iy][ix].reset();
        continue;
      }

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

  int count = 2 * (level < 10 ? 10 - level : level - 10);
  if (count > 20) count = 20;

  for (int i = 0; i < count; ++i) {
    int x = rand() % 8;
    if (level < 10) {
      for (int y = 13; y < 16; ++y) {
        if (tooth_piece(x, y)) {
          damage_tooth(x, y);
          break;
        }
      }
    } else {
      for (int y = 12; y >= 0; --y) {
        if (!piece(x, y)) {
          pieces[y][x].reset(new Candy(graphics, 0, static_cast<Candy::Color>(rand() % 4)));
          break;
        }
      }
    }
  }

  spawn_candy(graphics);
}

int GameGrid::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {
  drop_counter += elapsed;

  if (winner() || loser()) return 0;

  if (active_piece) {

    int move = 0;
    if (input.key_pressed(SDLK_LEFT) || input.key_pressed(SDLK_a)) {
      move = -1;
    } else if (input.key_pressed(SDLK_RIGHT) || input.key_pressed(SDLK_d)) {
      move = 1;
    }

    if (move != 0) {
      active_piece->slide(move < 0);
      if (collision(active_piece)) {
        audio.play_sample("bump");
        active_piece->slide(move > 0);
      }
    }


    int rotate = 0;
    if (input.key_pressed(SDLK_q)) {
      rotate = -1;
    } else if (input.key_pressed(SDLK_UP) || input.key_pressed(SDLK_w) || input.key_pressed(SDLK_e)) {
      rotate = 1;
    }

    if (rotate != 0) {
      active_piece->rotate(rotate > 0);
      if (collision(active_piece)) {
        audio.play_sample("bump");
        active_piece->rotate(rotate < 0);
      }
    }
  }

  if (drop_counter > drop_threshold(input.key_held(SDLK_DOWN) || input.key_held(SDLK_s))) {
    drop_counter = 0;

    if (falling_pieces.empty()) {
      if (!active_piece) spawn_candy(graphics);
      if (!active_piece) return 0;

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

    return process_matches(audio);
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

bool GameGrid::winner() {
  for (int iy = 0; iy < 16; ++iy) {
    for (int ix = 0; ix < 8; ++ix) {
      if (tooth_piece(ix, iy)) return false;
    }
  }
  return true;
}

bool GameGrid::loser() {
  return piece(3, 0) || piece(4, 0);
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

unsigned int GameGrid::drop_threshold(bool fast) {
  if (fast || !active_piece) return 50;
  return level > 10 ? 150 : 1500 / level;
}

CandyBlock* GameGrid::generate_candy(Graphics& graphics) {
  CandyBlock::Shape shape;
  int picker = rand() % 100;

  if (picker < 50)      { shape = CandyBlock::TWO;   }
  else if (picker < 85) { shape = CandyBlock::THREE; }
  else                  { shape = CandyBlock::FOUR;  }

  return new CandyBlock(graphics, shape, 3, 0);
}


void GameGrid::spawn_candy(Graphics& graphics) {
  if (!next_piece) next_piece.reset(generate_candy(graphics));

  active_piece = next_piece;
  next_piece.reset(generate_candy(graphics));

  for (int i = 0; i < 3; ++i) {
    if (!collision(active_piece)) return;
    active_piece->rotate();
  }

  active_piece.reset();
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

  return 10 * candy_count + 25 * tooth_count;
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


