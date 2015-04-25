#include "menu.h"

Menu::Menu(Graphics& graphics, std::list<std::string> options) : options(options) {
  text.reset(new Text(graphics));
  tooth.reset(new ToothSprite(graphics));
}

void Menu::draw(Graphics& graphics, unsigned int y, unsigned int choice) {
  int ty = y;

  for (std::list<std::string>::iterator i = options.begin(); i != options.end(); ++i) {
    text->draw(graphics, 320, ty, (*i), Text::CENTER);
    ty += 16;
  }

  tooth->draw(graphics, 256, y + choice * 16);
  tooth->draw(graphics, 368, y + choice * 16);
}
