#pragma once

#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>

class Audio {

  public:

    Audio();
    ~Audio();

    // TODO music

    void play_sample(std::string name);

    void pause() { Mix_Pause(-1); }
    void resume() { Mix_Resume(-1); }

  private:

    Mix_Chunk* load_clip(std::string file);

    typedef std::map<std::string, Mix_Chunk*> ChunkMap;
    ChunkMap chunks;

};
