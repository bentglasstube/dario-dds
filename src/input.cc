#include "input.h"

#define JOY_DEAD_ZONE 16000

Input::Input() : joystick(NULL) {
  for (int i = 0; i < SDL_NumJoysticks(); ++i) {
    joystick = SDL_JoystickOpen(i);
    break;
  }
}

Input::~Input() {
  if (joystick != NULL) SDL_JoystickClose(joystick);
}

void Input::joy_axis(const SDL_Event& event) {
  int dir = 0;
  if (event.jaxis.value < -JOY_DEAD_ZONE) dir = -1;
  if (event.jaxis.value >  JOY_DEAD_ZONE) dir =  1;

  Input::Action neg, pos;

  switch (event.jaxis.axis) {
    case 0:
    case 2:
      neg = Input::LEFT;
      pos = Input::RIGHT;
      break;

    case 1:
    case 3:
      neg = Input::UP;
      pos = Input::DOWN;
      break;

    case 4:
      pos = Input::CLOCKWISE;
      break;

    case 5:
      pos = Input::COUNTERCLOCKWISE;
      break;
  }

  switch (dir) {
    case -1:
      press_key(neg);
      release_key(pos);
      break;

    case 0:
      release_key(neg);
      release_key(pos);
      break;

    case 1:
      press_key(pos);
      release_key(neg);
      break;
  }
}

void Input::joy_hat(const SDL_Event& event) {
  int x = 0, y = 0;

  switch (event.jhat.value) {
    case SDL_HAT_LEFTUP:    x = -1; y = -1; break;
    case SDL_HAT_LEFT:      x = -1; y =  0; break;
    case SDL_HAT_LEFTDOWN:  x = -1; y =  1; break;
    case SDL_HAT_UP:        x =  0; y = -1; break;
    case SDL_HAT_CENTERED:  x =  0; y =  0; break;
    case SDL_HAT_DOWN:      x =  0; y =  1; break;
    case SDL_HAT_RIGHTUP:   x =  1; y = -1; break;
    case SDL_HAT_RIGHT:     x =  1; y =  0; break;
    case SDL_HAT_RIGHTDOWN: x =  1; y =  1; break;
  }

  switch (x) {
    case -1:
      press_key(Input::LEFT);
      release_key(Input::RIGHT);
      break;

    case 0:
      release_key(Input::LEFT);
      release_key(Input::RIGHT);
      break;

    case 1:
      release_key(Input::LEFT);
      press_key(Input::RIGHT);
      break;
  }

  switch (y) {
    case -1:
      press_key(Input::UP);
      release_key(Input::DOWN);
      break;

    case 0:
      release_key(Input::UP);
      release_key(Input::DOWN);
      break;

    case 1:
      release_key(Input::UP);
      press_key(Input::DOWN);
      break;
  }

}

Input::Action Input::key_mapping(const SDL_Keycode key) {
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

Input::Action Input::joy_mapping(const Uint8 button) {
  switch (button) {
    case 0:
    case 3:
    case 4:
      return Input::COUNTERCLOCKWISE;

    case 1:
    case 2:
    case 5:
      return Input::CLOCKWISE;

    case 6:
      return Input::BACK;

    case 7:
      return Input::ACCEPT;

    default:
      return Input::NONE;
  }
}
