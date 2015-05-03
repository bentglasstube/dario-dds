#pragma once

#include <SDL2/SDL.h>

class Graphics;

class Face {
  public:

    Face(Graphics& graphics);

    void reroll();
    void draw(Graphics& graphics, unsigned int x, unsigned int y);

  private:

    void draw_part(Graphics& graphics, unsigned int x, unsigned int y, unsigned int sx, unsigned int sy, unsigned int w, unsigned int h);

    SDL_Texture* texture;
    SDL_Rect rect;

    int tone, moustache;
    bool freckles, piercing;
};
