#pragma once

#include <SDL2/SDL.h>

class Graphics;

class GridPiece {

  public:

    GridPiece(Graphics& graphcis, unsigned int connections=0);

    void draw(Graphics& graphics, unsigned int x, unsigned int y);
    void set_connections(unsigned int connections);
    void rotate(bool clockwise=true);

    bool connected(unsigned int dir) { return (connections & dir) == dir; }
    void make_connection(unsigned int dir) { connections |= dir; }
    void break_connection(unsigned int dir) { connections &= ~dir; }

  protected:

    unsigned int connections;

  private:

    virtual void get_source(SDL_Rect* rect) = 0;

    SDL_Texture* texture;
};
