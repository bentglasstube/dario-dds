#pragma once

#include <memory>
#include <list>

#include "candy_block.h"
#include "crumble.h"
#include "floating_text.h"
#include "grid_piece.h"
#include "tooth.h"

class Audio;
class Graphics;
class Input;

class GameGrid {

  public:

    void generate(Graphics& graphics, int starting_level);
    int update(Input& input, Audio& audio, Graphics& graphics, int elapsed);
    void draw(Graphics& graphics, int x, int y);
    void draw_next_piece(Graphics& graphics, int x, int y) { next_piece->draw(graphics, x - 48, y); }

    bool winner();
    bool loser();

    int get_level() { return level; }
    void level_up() { level++; }

  private:

    struct Match {
      Match(int x, int y, int length, bool horizontal) : x(x), y(y), length(length), horizontal(horizontal) {}
      int x, y, length;
      bool horizontal;
    };

    std::shared_ptr<GridPiece> piece(int x, int y);
    std::shared_ptr<Candy> candy_piece(int x, int y);
    std::shared_ptr<Tooth> tooth_piece(int x, int y);

    int drop_threshold(bool fast);
    CandyBlock* generate_candy(Graphics& graphics);
    void spawn_candy(Graphics& graphics);
    bool collision(std::shared_ptr<CandyBlock> block);
    void release(int x, int y);
    void commit(std::shared_ptr<CandyBlock> block);
    int process_matches(Audio& audio, Graphics& graphics);
    bool remove_piece(Graphics& graphics, int x, int y);
    bool damage_tooth(Graphics& graphics, int x, int y);

    std::shared_ptr<GridPiece> pieces[16][8];
    int last_move, last_rotate, drop_counter, level, combo;
    int move, rotate;
    std::shared_ptr<CandyBlock> active_piece, next_piece;
    std::list<std::shared_ptr<CandyBlock> > falling_pieces;
    std::list<std::shared_ptr<Crumble> > crumbles;
    std::list<std::shared_ptr<FloatingText> > floating_texts;
};
