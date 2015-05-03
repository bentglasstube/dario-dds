#pragma once

#include <string>

class Audio;
class Graphics;
class Input;

class Screen {

  public:

    virtual void init(Graphics& graphics) {}
    virtual bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed) = 0;
    virtual void draw(Graphics& graphics) = 0;
    virtual Screen* next_screen() = 0;
    virtual std::string get_music_track() = 0;

    bool process_input(Input& input);

  protected:

    virtual void lost_focus() {}
};
