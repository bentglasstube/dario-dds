#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "graphics.h"

class Text {
  public:

    enum Alignment { LEFT, CENTER, RIGHT };

    Text(Graphics& graphics);

    void draw(Graphics& graphics, unsigned int x, unsigned int y, const std::string& text, Alignment alignment=LEFT);

  private:

    SDL_Texture* texture;
};

