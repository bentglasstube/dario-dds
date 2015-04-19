#include "backdrop.h"

#include "graphics.h"

Backdrop::Backdrop(Graphics& graphics, const std::string& file) {
  texture = graphics.load_image(file);
}

void Backdrop::draw(Graphics& graphics) {
  graphics.blit(texture, NULL, NULL);
}
