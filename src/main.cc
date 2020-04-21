#include <SDL2/SDL.h>

#include "game.h"

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
void step(void* game) {
  static_cast<Game*>(game)->step();
}
#endif

int main(int, char**) {
  Game game;

#ifdef __EMSCRIPTEN__
  game.start();
  emscripten_set_main_loop_arg(step, &game, 0, true);
#else
  game.loop();
#endif

  return 0;
}
