#pragma once

#include <string>
#include <SDL2/SDL.h>

class Graphics;

class Sprite {
  public:

    Sprite(Graphics& graphics, const std::string& file, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    void draw(Graphics& graphics, unsigned int x, unsigned int y);
    virtual void update() {}

  protected:

    SDL_Rect rect;

  private:

    SDL_Texture* texture;
};
