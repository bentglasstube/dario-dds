#pragma once

#include <string>

#include "text.h"

class FloatingText : public Text {

  public:

    FloatingText(Graphics& graphics, int x, int y, std::string text) : Text(graphics), x(16 * x), y(16 * y), counter(0), text(text) {}

    bool update(int elapsed);
    void draw(Graphics& graphics, int x, int y);

  private:

    int x, y, counter;
    std::string text;
};
