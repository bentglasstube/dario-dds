#pragma once

#include <map>
#include <SDL2/SDL.h>

class Input {
  public:

    enum Action {
      NONE             = 0,
      LEFT             = 1,
      RIGHT            = 2,
      UP               = 3,
      DOWN             = 4,
      ACCEPT           = 5,
      BACK             = 6,
      CLOCKWISE        = 3,  // same as up
      COUNTERCLOCKWISE = 7,
      FULLSCREEN       = 8,
    };

    void clear();
    void key_down(const SDL_Event& event);
    void key_up(const SDL_Event& event);

    bool key_pressed(Action key) { return keys_pressed[key]; }
    bool key_released(Action key) { return keys_released[key]; }
    bool key_held(Action key) { return keys_held[key]; }

  private:
    Action mapping(const SDL_Keycode key);

    std::map<Action, bool> keys_held;
    std::map<Action, bool> keys_pressed;
    std::map<Action, bool> keys_released;
};
