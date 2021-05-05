#include "game.h"

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#include "text.h"
#include "title_screen.h"
#include "screen.h"

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

void Game::start() {
  Text text(graphics);

  last_update = SDL_GetTicks();

  screen.reset(new TitleScreen());
  screen->init(graphics);
}

void Game::step() {
  const int start = SDL_GetTicks();

  // Start music if it's not playing
  if (Mix_PlayingMusic() == 0) audio.play_music(screen->get_music_track());

  if (!screen->process_input(input)) {
    screen.reset();
    return;
  }

  int now = SDL_GetTicks();
  if (screen->update(input, audio, graphics, now - last_update)) {

    graphics.clear();
    screen->draw(graphics);
    graphics.flip();

  } else {

    screen.reset(screen->next_screen());
    if (screen) screen->init(graphics);

    audio.stop_music();
  }

  last_update = now;

  const int elapsed = SDL_GetTicks() - start;
  if (MSPF > elapsed) SDL_Delay(MSPF - elapsed);
}

void Game::loop() {
  start();
  while (screen) {
    step();
  }
}
