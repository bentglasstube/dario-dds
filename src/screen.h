#pragma once

class Audio;
class Graphics;
class Input;

class Screen {
  public:

    Screen();
    ~Screen();

    virtual bool process_input(Audio& audio, Input& input);
    virtual bool update(Audio& audio, Graphics& graphics, unsigned int elapsed) = 0;
    virtual void draw(Graphics& graphics) = 0;
};
