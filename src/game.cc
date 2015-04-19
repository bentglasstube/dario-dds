#include "game.h"

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#include "audio.h"
#include "graphics.h"
#include "input.h"
#include "main_screen.h"
#include "screen.h"

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
  Audio audio;
  Input input;

  bool running = true;
  unsigned int last_update = SDL_GetTicks();

  current_screen = new MainScreen(graphics);

  while (running) {
    const unsigned int start = SDL_GetTicks();

    // TODO improve this process so that a screen can return a code to move on
    // to a different screen
    bool process = current_screen->process_input(audio, input);
    bool update = current_screen->update(audio, graphics, SDL_GetTicks() - last_update);
    running = process && update;

    last_update = SDL_GetTicks();
    draw(graphics);

    const unsigned int elapsed = SDL_GetTicks() - start;
    if (MSPF > elapsed) SDL_Delay(MSPF - elapsed);
  }
}

void Game::draw(Graphics& graphics) {
  graphics.clear();
  current_screen->draw(graphics);
  // TODO draw FPS
  graphics.flip();
}
