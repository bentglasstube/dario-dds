#pragma once

class Screen;
class Graphics;

class Game {
  public:

    Game();
    ~Game();

    void loop();

  private:

    void draw(Graphics& graphics);
    Screen* current_screen;
};
