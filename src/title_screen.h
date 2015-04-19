#pragma once

#include <boost/scoped_ptr.hpp>

#include "menu.h"
#include "backdrop.h"
#include "screen.h"

class TitleScreen : public Screen {

  public:

    void init(Audio& audio, Graphics& graphics);
    bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);
    Screen* next_screen();

  private:

    unsigned int choice;
    boost::scoped_ptr<Backdrop> backdrop;
    boost::scoped_ptr<Menu> menu;

};
