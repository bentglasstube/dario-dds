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

    bool any_key_pressed();
    bool key_pressed(SDL_Keycode key);
    bool key_released(SDL_Keycode key);
    bool key_held(SDL_Keycode key);

  private:
    std::map<SDL_Keycode, bool> keys_held;
    std::map<SDL_Keycode, bool> keys_pressed;
    std::map<SDL_Keycode, bool> keys_released;
};
