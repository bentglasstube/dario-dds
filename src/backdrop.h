#pragma once

#include <SDL2/SDL.h>
#include <string>

class Graphics;

class Backdrop {

  public:

    Backdrop(Graphics& graphics, const std::string& file);
    virtual ~Backdrop() {}

    void draw(Graphics& graphics);
    virtual void update() {}

  private:

    SDL_Texture* texture;

};
