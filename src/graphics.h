#pragma once

#include <string>
#include <map>

class SDL_Rect;
class SDL_Renderer;
class SDL_Texture;
class SDL_Window;

class Graphics {
  public:

    Graphics();
    ~Graphics();

    void blit(SDL_Texture* source, SDL_Rect* srect, SDL_Rect* drect);
    void flip();
    void clear();

    SDL_Texture* load_image(std::string file, bool transparency=false);

  private:

    typedef std::map<std::string, SDL_Texture*> TextureMap;
    TextureMap textures;
    SDL_Window* window;
    SDL_Renderer* renderer;
};
