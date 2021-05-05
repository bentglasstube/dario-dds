#pragma once

#include <memory>

#include "backdrop.h"
#include "screen.h"
#include "sprite.h"
#include "text.h"
#include "tooth_sprite.h"

class SettingsScreen : public Screen {

  public:

    void init(Graphics& graphics);
    bool update(Input& input, Audio& audio, Graphics& graphics, int elapsed);
    void draw(Graphics& graphics);
    Screen* next_screen();
    std::string get_music_track() { return "waitingroom"; }

  private:

    void change(bool increase, Audio& audio);

    std::unique_ptr<Backdrop> backdrop;
    std::unique_ptr<Text> text;
    std::unique_ptr<ToothSprite> tooth;
    std::unique_ptr<Sprite> left;
    std::unique_ptr<Sprite> right;

    int choice, value[4], min[4], max[4];

};
