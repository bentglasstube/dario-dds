#pragma once

#include <SDL2/SDL.h>

class Graphics;

class GridPiece {

  public:

    GridPiece(Graphics& graphcis);

    void draw(Graphics& graphics, unsigned int x, unsigned int y);
    void set_connections(unsigned int connections);

  protected:

    unsigned int connections;

  private:

    virtual void get_source(SDL_Rect* rect) = 0;

    SDL_Texture* texture;
};
