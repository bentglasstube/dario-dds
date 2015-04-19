#pragma once

#include <boost/scoped_ptr.hpp>
#include <list>
#include <string>

#include "sprite.h"
#include "text.h"

class Menu {

  public:

    Menu(Graphics& graphics, std::list<std::string> options);

    void draw(Graphics& graphics, unsigned int y, unsigned int choice);

  private:

    std::list<std::string> options;
    boost::scoped_ptr<Text> text;
    boost::scoped_ptr<Sprite> tooth;
};
