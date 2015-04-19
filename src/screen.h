#pragma once

class Audio;
class Graphics;
class Input;

class Screen {

  public:

    virtual void init(Audio& audio, Graphics& graphics) {}
    virtual bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) = 0;
    virtual void draw(Graphics& graphics) = 0;
    virtual Screen* next_screen() = 0;

    bool process_input(Input& input);

};
