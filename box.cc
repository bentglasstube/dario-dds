#include "box.h"

#include "graphics.h"

Box::Box(Graphics& graphics) {
  texture = graphics.load_image("ui", true);
}

SDL_Rect* _rect(SDL_Rect* rect, int x, int y, int w, int h) {
  rect->x = x;
  rect->y = y;
  rect->w = w;
  rect->h = h;

  return rect;
}

void Box::draw(Graphics& graphics, int x, int y, int w, int h) {
  SDL_Rect source, dest;

  const int ex = x + w - 16;
  const int ey = y + h - 16;

  // corners
  graphics.blit(texture, _rect(&source, 16,  0, 16, 16), _rect(&dest,  x,  y, 16, 16));
  graphics.blit(texture, _rect(&source, 32,  0, 16, 16), _rect(&dest, ex,  y, 16, 16));
  graphics.blit(texture, _rect(&source, 16, 16, 16, 16), _rect(&dest,  x, ey, 16, 16));
  graphics.blit(texture, _rect(&source, 32, 16, 16, 16), _rect(&dest, ex, ey, 16, 16));

  // sides
  graphics.blit(texture, _rect(&source, 32,  0,  4, 16), _rect(&dest, x + 16,  y, w - 32, 16));
  graphics.blit(texture, _rect(&source, 32, 16,  4, 16), _rect(&dest, x + 16, ey, w - 32, 16));
  graphics.blit(texture, _rect(&source, 16, 16, 16,  4), _rect(&dest,  x, y + 16, 16, h - 32));
  graphics.blit(texture, _rect(&source, 32, 16, 16,  4), _rect(&dest, ex, y + 16, 16, h - 32));

  // middle
  graphics.blit(texture, _rect(&source, 32, 16,  4,  4), _rect(&dest, x + 16, y + 16, w - 32, h - 32));
}
