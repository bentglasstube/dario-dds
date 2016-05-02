#pragma once

#include <boost/scoped_ptr.hpp>
#include <list>
#include <string>

#include "text.h"
#include "tooth_sprite.h"

class Menu {

  public:

    Menu(Graphics& graphics, std::list<std::string> options);

    void draw(Graphics& graphics, int y, int choice);

  private:

    std::list<std::string> options;
    boost::scoped_ptr<Text> text;
    boost::scoped_ptr<ToothSprite> tooth;
};
