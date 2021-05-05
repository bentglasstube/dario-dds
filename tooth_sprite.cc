#include "tooth_sprite.h"

#include <SDL2/SDL.h>

#include "graphics.h"

ToothSprite::ToothSprite(Graphics& graphics) : Sprite(graphics, "ui", 0, 0, 16, 16) {}

void ToothSprite::draw(Graphics& graphics, int x, int y) {
  int offset = SDL_GetTicks() % 1000;

  if (offset >= 850) {
    rect.y = (offset - 800) / 50 * 16;
  } else {
    rect.y = 0;
  }

  Sprite::draw(graphics, x, y);
}
