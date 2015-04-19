#pragma once

#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>

class Audio {

  public:

    Audio();
    ~Audio();

    void play_sample(std::string name);

    void pause() { Mix_Pause(-1); }
    void resume() { Mix_Resume(-1); }

    void play_music(std::string name);
    void stop_music() { Mix_FadeOutMusic(1000); }

  private:

    Mix_Chunk* load_chunk(std::string file);
    Mix_Music* load_music(std::string file);

    typedef std::map<std::string, Mix_Chunk*> ChunkMap;
    typedef std::map<std::string, Mix_Music*> MusicMap;

    ChunkMap chunks;
    MusicMap musics;

};
