#pragma once

#include <SDL2/SDL.h>

class Graphics;

class Face {
  public:

    Face(Graphics& graphics);

    void reroll();
    void draw(Graphics& graphics, int x, int y);

  private:

    void draw_part(Graphics& graphics, int x, int y, int sx, int sy, int w, int h);

    SDL_Texture* texture;
    SDL_Rect rect;

    int tone, moustache, nose;
    bool freckles, piercing;
};
