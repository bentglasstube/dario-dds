#pragma once

#include <SDL2/SDL.h>

class Graphics;

class Box {

  public:

    Box(Graphics& graphics);

    void draw(Graphics& graphics, int x, int y, int w, int h);

  private:

    SDL_Texture* texture;

};
