#pragma once

#include <boost/scoped_ptr.hpp>

#include "backdrop.h"
#include "screen.h"
#include "text.h"

class Settings : public Screen {

  public:

    void init(Audio& audio, Graphics& graphics);
    bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);
    Screen* next_screen();

  private:

    boost::scoped_ptr<Backdrop> backdrop;
    boost::scoped_ptr<Text> text;

};
