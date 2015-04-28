#include "text.h"

Text::Text(Graphics &graphics) : Sprite(graphics, "text", 0, 0, 8, 16) {}

void Text::draw(Graphics& graphics, unsigned int x, unsigned int y, std::string text, Text::Alignment alignment) {
  switch (alignment) {
    case Text::LEFT:
      break;

    case Text::CENTER:
      x -= 4 * text.length();
      break;

    case Text::RIGHT:
      x -= 8 * text.length();
      break;
  }

  for (std::string::iterator i = text.begin(); i != text.end(); ++i) {
    int n = 29;
    if ((*i) >= 'A' && (*i) <= 'Z') {
      n = (*i) - 'A';
    } else if ((*i) >= 'a' && (*i) <= 'z') {
      n = (*i) - 'a';
    } else if ((*i) >= '0' && (*i) <= '9') {
      n = (*i) - '0' + 30;
    } else if ((*i) == '.') {
      n = 26;
    } else if ((*i) == '!') {
      n = 27;
    } else if ((*i) == '?') {
      n = 28;
    }

    rect.x = 8 * (n % 10);
    rect.y = 16 * (n / 10);

    Sprite::draw(graphics, x, y);

    x += 8;
  }
}
