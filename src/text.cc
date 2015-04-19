#include "text.h"

Text::Text(Graphics &graphics) : Sprite(graphics, "text", 0, 0, 8, 16) {}

void Text::draw(Graphics& graphics, unsigned int x, unsigned int y, std::string text, bool centered) {
  if (centered) x -= 4 * text.length();

  for (std::string::iterator i = text.begin(); i != text.end(); ++i) {
    int n = 27;
    if ((*i) >= 'A' && (*i) <= 'Z') {
      n = (*i) - 'A';
    } else if ((*i) >= 'a' && (*i) <= 'z') {
      n = (*i) - 'a';
    } else if ((*i) >= '0' && (*i) <= '9') {
      n = (*i) - '0' + 30;
    }

    rect.x = 8 * (n % 10);
    rect.y = 16 * (n / 10);

    Sprite::draw(graphics, x, y);

    x += 8;
  }
}
