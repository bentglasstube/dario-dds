#pragma once

#include <boost/scoped_ptr.hpp>

#include "backdrop.h"
#include "screen.h"
#include "sprite.h"
#include "text.h"
#include "tooth_sprite.h"

class SettingsScreen : public Screen {

  public:

    void init(Audio& audio, Graphics& graphics);
    bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);
    Screen* next_screen();

  private:

    void change(bool increase, Audio& audio);

    boost::scoped_ptr<Backdrop> backdrop;
    boost::scoped_ptr<Text> text;
    boost::scoped_ptr<ToothSprite> tooth;
    boost::scoped_ptr<Sprite> left;
    boost::scoped_ptr<Sprite> right;

    int choice, value[4], min[4], max[4];

};
