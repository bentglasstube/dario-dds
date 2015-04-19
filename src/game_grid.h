#pragma once

#include <boost/shared_ptr.hpp>
#include <list>

#include "grid_piece.h"
#include "candy_block.h"
#include "tooth.h"

class Audio;
class Graphics;
class Input;

class GameGrid {

  public:

    void generate(Graphics& graphics, unsigned int starting_level);
    int update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics, unsigned int x, unsigned int y);
    void draw_next_piece(Graphics& graphics, unsigned int x, unsigned int y) { next_piece->draw(graphics, x - 48, y); }

    bool winner();
    bool loser();

    unsigned int get_level() { return level; }
    void level_up() { level++; }

  private:

    struct Match {
      Match(unsigned int x, unsigned int y) : x(x), y(y) {}
      unsigned int x;
      unsigned int y;
    };

    boost::shared_ptr<GridPiece> piece(int x, int y);
    boost::shared_ptr<Candy> candy_piece(int x, int y);
    boost::shared_ptr<Tooth> tooth_piece(int x, int y);

    unsigned int drop_threshold(bool fast);
    CandyBlock* generate_candy(Graphics& graphics);
    void spawn_candy(Graphics& graphics);
    bool collision(boost::shared_ptr<CandyBlock> block);
    void release(int x, int y);
    void commit(boost::shared_ptr<CandyBlock> block);
    int process_matches(Audio& audio);
    bool remove_piece(int x, int y);
    bool damage_tooth(int x, int y);

    boost::shared_ptr<GridPiece> pieces[16][8];
    unsigned int drop_counter, level;
    boost::shared_ptr<CandyBlock> active_piece, next_piece;
    std::list<boost::shared_ptr<CandyBlock> > falling_pieces;
};
