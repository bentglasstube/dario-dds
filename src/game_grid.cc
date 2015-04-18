#include "game_grid.h"

#include "candy.h"
#include "graphics.h"
#include "tooth.h"

GameGrid::GameGrid() :
  move_counter(0), drop_counter(0), drop_speed(10),
  active_x(0), active_y(0),
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

      pieces[iy][ix].reset(new Tooth(graphics, connections, (rand() % 2) == 0));
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

  if (move_counter > 100) {
    move_counter = 0;
    if (_move != 0) {
      if (collision(active_x + _move, active_y)) {
        // TODO play bump sound
      } else {
        active_x += _move;
      }
      _move = 0;
    }


    if (_rotate != 0) {
      active_piece->rotate(_rotate > 0);
      if (collision(active_x, active_y)) {
        // TODO play bump sound
        active_piece->rotate(_rotate < 0);
      }

      _rotate = 0;
    }
  }

  if (drop_counter > drop_threshold()) {
    drop_counter = 0;

    if (collision(active_x, active_y + 1)) {
      // TODO play bump sound
      fprintf(stderr, "Piece landed, committing\n");

      commit_active();

      /* TODO make the candy drop and shit
       *
       *    check for matches
       *      rot teeth
       *      drop things down
       *    start new candy falling
       *    generate next candy
       *
       */

      if (!spawn_candy(graphics)) {
        fprintf(stderr, "Nowhere to place candy, game over\n");
        return -1;
      }
    } else {
      active_y++;
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

  if (active_piece) active_piece->draw(graphics, x + 16 * active_x, y + 16 * active_y);
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

  active_piece.reset(new CandyBlock(graphics, shape));

  // sorry, this is insane
  // it basically searches from the middle out for a spot to put the piece
  // the idea is for the loop to iterate over the values 3, 4, 2, 5, 1, 6, 0, 7
  for (int tx = 3; tx >= 0; tx = (tx > 3 ? 6 : 7) - tx) {
    if (!collision(tx, 0)) {
      active_x = tx;
      active_y = 0;

      return true;
    }
  }

  active_piece.reset();

  return false;
}

bool GameGrid::collision(int x, int y) {
  if (!active_piece) return false;

  for (int iy = 0; iy < 2; ++iy) {
    for (int ix = 0; ix < 2; ++ix) {
      if (active_piece->piece_at(ix, iy)) {
        if (x + ix < 0 || x + ix >= 8) return true;
        if (y + iy < 0 || y + iy >= 16) return true;
        if (pieces[y + iy][x + ix]) return true;
      }
    }
  }

  return false;
}

void GameGrid::commit_active() {
  for (int iy = 0; iy < 2; ++iy) {
    for (int ix = 0; ix < 2; ++ix) {
      if (active_piece->piece_at(ix, iy)) pieces[active_y + iy][active_x + ix] = active_piece->piece_at(ix, iy);
    }
  }
}
