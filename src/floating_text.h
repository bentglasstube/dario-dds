#pragma once

#include <string>

#include "text.h"

class FloatingText : public Text {

  public:

    FloatingText(Graphics& graphics, unsigned int x, unsigned int y, std::string text) : Text(graphics), x(16 * x), y(16 * y), counter(0), text(text) {}

    bool update(unsigned int elapsed);
    void draw(Graphics& graphics, unsigned int x, unsigned int y);

  private:

    unsigned int x, y, counter;
    std::string text;
};
