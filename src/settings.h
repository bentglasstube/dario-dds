#pragma once

class Settings {

  public:

    static Settings& get_instance() {
      static Settings instance;
      return instance;
    }

    int sfx_volume, music_volume, music_track, starting_level;

  private:

    Settings() : sfx_volume(10), music_volume(10), music_track(0), starting_level(1) {}

    // Deliberatlye unimplemented
    Settings(Settings const&);
    void operator=(Settings const&);

};
