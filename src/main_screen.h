#pragma once

#include <boost/scoped_ptr.hpp>

#include "screen.h"

class Graphics;
class Sprite;

class MainScreen : public Screen {
  public:
    MainScreen(Graphics& graphics);

    bool update(unsigned int elapsed);
    void draw(Graphics& graphics);

  private:

    // TODO save all the game objects
    boost::scoped_ptr<Sprite> tooth_tl;
    boost::scoped_ptr<Sprite> tooth_tc;
    boost::scoped_ptr<Sprite> tooth_tr;
    boost::scoped_ptr<Sprite> tooth_ml;
    boost::scoped_ptr<Sprite> tooth_mc;
    boost::scoped_ptr<Sprite> tooth_mr;
};
