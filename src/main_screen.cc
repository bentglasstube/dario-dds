#include "main_screen.h"

#include "audio.h"
#include "input.h"
#include "text.h"
#include "title_screen.h"

void MainScreen::init(Audio& audio, Graphics& graphics) {
  audio.play_music("rootcanal");

  game_grid = GameGrid();
  game_grid.generate(graphics);

  state = PLAYING;

  text.reset(new Text(graphics));
  box.reset(new Box(graphics));
  backdrop.reset(new Backdrop(graphics, "game"));
}

bool MainScreen::update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) {

  if (input.key_pressed(SDLK_ESCAPE) || input.key_pressed(SDLK_BACKQUOTE)) {
    return false;
  }

  if (input.key_pressed(SDLK_SPACE) || input.key_pressed(SDLK_RETURN)) {
    if (state == PAUSED) {
      audio.play_sample("pause");
      state = PLAYING;
    } else if (state == PLAYING) {
      audio.play_sample("pause");
      state = PAUSED;
    }
  }

  if (state == PLAYING) {

    if (input.key_pressed(SDLK_LEFT) || input.key_pressed(SDLK_a)) {
      game_grid.move(-1);
    } else if (input.key_pressed(SDLK_RIGHT) || input.key_pressed(SDLK_d)) {
      game_grid.move(1);
    }

    if (input.key_pressed(SDLK_q)) {
      game_grid.rotate(-1);
    } else if (input.key_pressed(SDLK_UP) || input.key_pressed(SDLK_w) || input.key_pressed(SDLK_e)) {
      game_grid.rotate(1);
    }

    if (input.key_pressed(SDLK_DOWN) || input.key_pressed(SDLK_s)) {
      game_grid.drop(true);
    } else if (input.key_released(SDLK_DOWN) || input.key_released(SDLK_s)) {
      game_grid.drop(false);
    }

    switch (game_grid.update(audio, graphics, elapsed)) {
      case -1:
        state = GAME_OVER;
        break;

      case 1:
        state = VICTORY;
        break;
    }

  } else if (input.key_pressed(SDLK_r)) {

    game_grid = GameGrid();
    game_grid.generate(graphics);
    state = PLAYING;

  }

  return true;
}

void MainScreen::draw(Graphics& graphics) {
  backdrop->draw(graphics);

  text->draw(graphics, 512, 128, "Next");

  game_grid.draw(graphics, 256, 176);
  game_grid.draw_next_piece(graphics, 512, 144);

  switch (state) {

    case PAUSED:

      text->draw(graphics, 320, 232, "Paused", true);
      break;

    case GAME_OVER:

      text->draw(graphics, 320, 232, "Game Over", true);
      break;

    case VICTORY:

      text->draw(graphics, 320, 232, "You Win!", true);
      break;

    case PLAYING:

      break;

  }
}

Screen * MainScreen::next_screen() { return new TitleScreen(); }
