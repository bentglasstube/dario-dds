#pragma once

#include <SDL2/SDL.h>
#include <string>

class Graphics;

class Sprite {
  public:

    Sprite(Graphics& graphics, const std::string& file, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    virtual void draw(Graphics& graphics, unsigned int x, unsigned int y);
    virtual bool update(unsigned int elapsed) { return true; }

  protected:

    SDL_Rect rect;

  private:

    SDL_Texture* texture;
};
