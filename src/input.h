#pragma once

#include <map>
#include <SDL2/SDL.h>

class Input {
  public:

    Input();
    ~Input();

    void clear();
    void key_down(const SDL_Event& event);
    void key_up(const SDL_Event& event);

    bool any_key_pressed() { return !keys_pressed.empty(); }

    bool key_pressed(SDL_Keycode key) { return keys_pressed[key]; }
    bool key_released(SDL_Keycode key) { return keys_released[key]; }
    bool key_held(SDL_Keycode key) { return keys_held[key]; }

  private:
    std::map<SDL_Keycode, bool> keys_held;
    std::map<SDL_Keycode, bool> keys_pressed;
    std::map<SDL_Keycode, bool> keys_released;
};
