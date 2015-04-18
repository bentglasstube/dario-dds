#include "sprite.h"

#include "graphics.h"

Sprite::Sprite(Graphics& graphics, const std::string& file, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
  texture = graphics.load_image(file, true);

  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
}

void Sprite::draw(Graphics& graphics, unsigned int x, unsigned int y) {
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;
  dest.w = rect.w;
  dest.h = rect.h;

  graphics.blit(texture, &rect, &dest);
}
