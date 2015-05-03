#include "face.h"

#include "graphics.h"

#define PART_WIDTH 224
#define PART_HEIGHT 160

Face::Face(Graphics& graphics) {
  texture = graphics.load_image("faces", true);
  reroll();
}

void Face::reroll() {
  tone = rand() % 4;

  freckles = rand() % 4 == 0;
  piercing = rand() % 10 == 0;

  if (rand() % 4 == 0) {
    moustache = rand() % 3 + 1;
  } else {
    moustache = 0;
  }

  int nose_select = rand() % 100;
  if (nose_select < 33) nose = 0;
  else if (nose_select < 99) nose = 1;
  else nose = 2;
}

void Face::draw(Graphics& graphics, unsigned int x, unsigned int y) {
  /* face */         draw_part(graphics, x, y, PART_WIDTH * tone, 0, PART_WIDTH, 3 * PART_HEIGHT);
  if (freckles)      draw_part(graphics, x, y, 5 * PART_WIDTH, 0, PART_WIDTH, PART_HEIGHT);
  /* nose */         draw_part(graphics, x, y, PART_WIDTH * 4, PART_HEIGHT * nose, PART_WIDTH, PART_HEIGHT);
  if (piercing)      draw_part(graphics, x, y + 2 * PART_HEIGHT, 5 * PART_WIDTH, 2 * PART_HEIGHT, PART_WIDTH, PART_HEIGHT);
  if (moustache > 0) draw_part(graphics, x, y, 6 * PART_WIDTH, PART_HEIGHT * (moustache - 1), PART_WIDTH, PART_HEIGHT);
}

void Face::draw_part(Graphics& graphics, unsigned int x, unsigned int y, unsigned int sx, unsigned int sy, unsigned int w, unsigned int h) {
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;

  rect.x = sx;
  rect.y = sy;

  rect.w = dest.w = w;
  rect.h = dest.h = h;

  graphics.blit(texture, &rect, &dest);
}
