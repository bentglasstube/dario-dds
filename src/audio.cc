#include "audio.h"

Audio::Audio() {
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

}

Audio::~Audio() {
  Mix_HaltChannel(-1);

  for (ChunkMap::iterator i = chunks.begin(); i != chunks.end(); ++i) {
    Mix_FreeChunk(i->second);
  }

  Mix_CloseAudio();
}

void Audio::play_sample(std::string name) {
  Mix_Chunk* chunk = load_clip(name);
  Mix_PlayChannel(-1, chunk, 0);
}

Mix_Chunk* Audio::load_clip(std::string file) {
  const std::string path("content/" + file + ".wav");
  if (chunks.count(path) == 0) {
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    chunks[path] = chunk;
  }

  return chunks[path];
}
