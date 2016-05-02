#include "text.h"

Text::Text(Graphics& graphics) {
  texture = graphics.load_image("text", true);
}

void Text::draw(Graphics& graphics, unsigned int x, unsigned int y, const std::string& text, Text::Alignment alignment) {
  SDL_Rect source = { 0, 0, 8, 16 };
  SDL_Rect dest = { x, y, 8, 16 };

  switch (alignment) {
    case LEFT:
      break;

    case CENTER:
      dest.x -= 4 * text.length();
      break;

    case RIGHT:
      dest.x -= 8 * text.length();
      break;
  }

  for (std::string::const_iterator i = text.begin(); i != text.end(); ++i) {
    int n = 0;
    if ((*i) >= ' ' && (*i) <= '~') n = (*i) - ' ';

    source.x = 8 * (n % 16);
    source.y = 16 * (n / 16);

    graphics.blit(texture, &source, &dest);

    if ((*i) == '\n' && alignment == LEFT) {
      dest.x = x;
      dest.y += 16;
    } else {
      dest.x += 8;
    }
  }
}
