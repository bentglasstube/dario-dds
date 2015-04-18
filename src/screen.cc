#include "screen.h"

#include "graphics.h"
#include "input.h"

Screen::Screen() {}
Screen::~Screen() {}

bool Screen::process_input(Input& input) {
  SDL_Event event;

  input.clear();

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
        input.key_down(event);
        break;

      case SDL_KEYUP:
        input.key_up(event);
        break;

      case SDL_QUIT:
        return false;

    }
  }

  return true;
}
