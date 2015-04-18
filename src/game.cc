#include "game.h"

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

namespace {
  const unsigned int FPS = 60;
  const unsigned int MSPF = 1000 / FPS;
}

Game::Game() {
  srand(static_cast<unsigned int>(time(NULL)));
  SDL_Init(SDL_INIT_EVERYTHING);
}

Game::~Game() {
  SDL_Quit();
}

void Game::loop() {
  Graphics graphics;

  bool running = true;
  unsigned int last_update = SDL_GetTicks();

  while (running) {
    const unsigned int start = SDL_GetTicks();

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT:
          running = false;
          break;
      }
    }

    // TODO update scene
    last_update = SDL_GetTicks();
    draw(graphics);

    const unsigned int elapsed = SDL_GetTicks() - start;
    if (MSPF > elapsed) SDL_Delay(MSPF - elapsed);
  }
}

void Game::draw(Graphics& graphics) {
  graphics.clear();
  // TODO draw scene
  graphics.flip();
}
