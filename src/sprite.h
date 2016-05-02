#pragma once

#include <SDL2/SDL.h>
#include <string>

class Graphics;

class Sprite {
  public:

    Sprite(Graphics& graphics, const std::string& file, int x, int y, int w, int h);

    virtual void draw(Graphics& graphics, int x, int y);
    virtual bool update(int) { return true; }

  protected:

    SDL_Rect rect;

  private:

    SDL_Texture* texture;
};
