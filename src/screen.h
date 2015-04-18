#pragma once

class Graphics;
class Input;

class Screen {
  public:

    Screen();
    ~Screen();

    virtual bool process_input(Input& input);
    virtual bool update(Graphics& graphics, unsigned int elapsed) = 0;
    virtual void draw(Graphics& graphics) = 0;
};
