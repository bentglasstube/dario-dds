#pragma once

#include <SDL2/SDL.h>

class Graphics;

class Box {

  public:

    Box(Graphics& graphics);

    void draw(Graphics& graphics, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

  private:

    SDL_Texture* texture;

};
