#include "game.h"

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#include "audio.h"
#include "graphics.h"
#include "input.h"
#include "text.h"
#include "title_screen.h"
#include "screen.h"

#define SHOW_FPS false

namespace {
  const int FPS = 60;
  const int MSPF = 1000 / FPS;
}

Game::Game() {
  srand(static_cast<int>(time(NULL)));
  SDL_Init(SDL_INIT_EVERYTHING);
}

Game::~Game() {
  SDL_Quit();
}

void Game::loop() {
  Graphics graphics;
  Audio audio;
  Input input;

  Text text(graphics);

  int last_update = SDL_GetTicks();
  int last_frame = SDL_GetTicks();

  screen.reset(new TitleScreen());
  screen->init(graphics);

  while (true) {
    const int start = SDL_GetTicks();

    // Start music if it's not playing
    if (Mix_PlayingMusic() == 0) audio.play_music(screen->get_music_track());

    if (!screen->process_input(input)) return;

    if (input.key_pressed(Input::FULLSCREEN)) graphics.toggle_full_screen();

    if (screen->update(input, audio, graphics, SDL_GetTicks() - last_update)) {

      graphics.clear();

      screen->draw(graphics);
      float fps = 1000.0f / (SDL_GetTicks() - last_frame);
      last_frame = SDL_GetTicks();

      graphics.flip();

    } else {

      screen.reset(screen->next_screen());
      if (!screen) return;
      screen->init(graphics);

      audio.stop_music();
    }

    last_update = SDL_GetTicks();

    const int elapsed = SDL_GetTicks() - start;
    if (MSPF > elapsed) SDL_Delay(MSPF - elapsed);
  }
}
