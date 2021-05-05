#pragma once

#include <SDL2/SDL.h>

class Graphics;

class GridPiece {

  public:

    GridPiece(Graphics& graphics, int connections=0);

    void draw(Graphics& graphics, int x, int y);
    void set_connections(int connections);
    void rotate(bool clockwise=true);

    bool connected(int dir) { return (connections & dir) == dir; }
    void make_connection(int dir) { connections |= dir; }
    void break_connection(int dir) { connections &= ~dir; }

  protected:

    int connections;

  private:

    virtual void get_source(SDL_Rect* rect) = 0;

    SDL_Texture* texture;
};
