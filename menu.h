#pragma once

#include <memory>
#include <list>
#include <string>

#include "text.h"
#include "tooth_sprite.h"

class Menu {

  public:

    Menu(Graphics& graphics, std::list<std::string> options);
    virtual ~Menu() {}

    void draw(Graphics& graphics, int y, int choice);

  private:

    std::list<std::string> options;
    std::unique_ptr<Text> text;
    std::unique_ptr<ToothSprite> tooth;
};
