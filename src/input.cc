#include "input.h"

void Input::clear() {
  keys_pressed.clear();
  keys_released.clear();
}

void Input::key_down(const SDL_Event& event) {
  keys_pressed[mapping(event.key.keysym.sym)] = true;
  keys_held[mapping(event.key.keysym.sym)] = true;
}

void Input::key_up(const SDL_Event& event) {
  keys_released[mapping(event.key.keysym.sym)] = true;
  keys_held[mapping(event.key.keysym.sym)] = false;
}

Input::Action Input::mapping(const SDL_Keycode key) {
  switch (key) {
    case SDLK_a:
    case SDLK_LEFT:
      return Input::LEFT;

    case SDLK_d:
    case SDLK_RIGHT:
      return Input::RIGHT;

    case SDLK_w:
    case SDLK_UP:
      return Input::UP;

    case SDLK_s:
    case SDLK_DOWN:
      return Input::DOWN;

    case SDLK_SPACE:
    case SDLK_RETURN:
      return Input::ACCEPT;

    case SDLK_ESCAPE:
    case SDLK_BACKQUOTE:
      return Input::BACK;

    case SDLK_e:
      return Input::CLOCKWISE;

    case SDLK_q:
      return Input::COUNTERCLOCKWISE;

    case SDLK_f:
      return Input::FULLSCREEN;

    default:
      return Input::NONE;
  }
}
