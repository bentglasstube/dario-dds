#include <SDL2/SDL.h>

#include "game.h"

int main(int, char**) {
  Game game;
  game.loop();

  fprintf(stderr, "");

  return 0;
}
