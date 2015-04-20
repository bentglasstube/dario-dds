#include <SDL2/SDL.h>

#include "game.h"

int main(int argc, char* argv[]) {
  Game game;
  game.loop();

  fprintf(stderr, "");

  return 0;
}
