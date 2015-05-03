#pragma once

#include <map>
#include <SDL2/SDL.h>

class Input {
  public:

    enum Action { NONE, LEFT, RIGHT, UP, DOWN, ACCEPT, BACK, CLOCKWISE, COUNTERCLOCKWISE, FULLSCREEN };

    Input();
    ~Input();

    void clear();
    void key_down(const SDL_Event& event) { press_key(key_mapping(event.key.keysym.sym)); };
    void key_up(const SDL_Event& event) { release_key(key_mapping(event.key.keysym.sym)); };
    void joy_down(const SDL_Event& event) { press_key(joy_mapping(event.jbutton.button)); };
    void joy_up(const SDL_Event& event) { release_key(joy_mapping(event.jbutton.button)); };
    void joy_axis(const SDL_Event& event);
    void joy_hat(const SDL_Event& event);

    bool key_pressed(Action key) { return keys_pressed[key]; }
    bool key_released(Action key) { return keys_released[key]; }
    bool key_held(Action key) { return keys_held[key]; }

  private:
    void press_key(const Action key) { keys_pressed[key] = true; keys_held[key] = true; }
    void release_key(const Action key) { keys_released[key] = true; keys_held[key] = false; }

    Action key_mapping(const SDL_Keycode key);
    Action joy_mapping(const Uint8 button);

    std::map<Action, bool> keys_held;
    std::map<Action, bool> keys_pressed;
    std::map<Action, bool> keys_released;

    SDL_Joystick* joystick;
};
