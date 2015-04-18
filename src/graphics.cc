#include "graphics.h"

#include "game.h"

namespace {
  const unsigned int width = 320;
  const unsigned int height = 240;
}

Graphics::Graphics() {
  int flags = SDL_WINDOW_OPENGL ; //| SDL_WINDOW_RESIZABLE;

  window = SDL_CreateWindow("Dr. Dario, DDS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
  renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"); // retro!
  SDL_RenderSetLogicalSize(renderer, width, height);
}

Graphics::~Graphics() {
  for (TextureMap::iterator i = textures.begin(); i != textures.end(); ++i) {
    SDL_DestroyTexture(i->second);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Graphics::blit(SDL_Texture* source, SDL_Rect* srect, SDL_Rect* drect) {
  SDL_RenderCopy(renderer, source, srect, drect);
}

void Graphics::flip() {
  SDL_RenderPresent(renderer);
}

void Graphics::clear() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

SDL_Texture* Graphics::load_image(std::string file, bool transparency) {
  const std::string path("content/" + file + ".bmp");
  if (textures.count(path) == 0) {
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (transparency) {
      const Uint32 black = SDL_MapRGB(surface->format, 0, 0, 0);
      SDL_SetColorKey(surface, SDL_TRUE, black);
    }

    textures[path] = SDL_CreateTextureFromSurface(renderer, surface);
  }

  return textures[path];
}
