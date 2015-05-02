#include "game.h"

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#include "audio.h"
#include "graphics.h"
#include "input.h"
#include "title_screen.h"
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

  unsigned int last_update = SDL_GetTicks();

  screen.reset(new TitleScreen());
  screen->init(audio, graphics);

  while (true) {
    const unsigned int start = SDL_GetTicks();

    if (!screen->process_input(input)) return;

    if (input.key_pressed(Input::FULLSCREEN)) graphics.toggle_full_screen();

    if (screen->update(input, audio, graphics, SDL_GetTicks() - last_update)) {

      graphics.clear();
      screen->draw(graphics);
      // TODO draw FPS
      graphics.flip();

    } else {

      screen.reset(screen->next_screen());
      if (!screen) return;
      screen->init(audio, graphics);

    }

    last_update = SDL_GetTicks();

    const unsigned int elapsed = SDL_GetTicks() - start;
    if (MSPF > elapsed) SDL_Delay(MSPF - elapsed);
  }
}
