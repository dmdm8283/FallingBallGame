#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class Audio {
public:
    Audio();
    ~Audio();

    bool initialize();
    bool loadMp3(const std::string& hitFilePath, const std::string& deathFilePath, const std::string& levelUpFilePath, const std::string& ostFilePath);
    void playHitSound();
    void playDeathSound();
    void playLevelUpSound();
    void playOst();
    void cleanup();

private:
    Mix_Chunk* hitSound;  
    Mix_Chunk* deathSound; 
    Mix_Chunk* levelUpSound; 
    Mix_Music* ost;
};

#endif // AUDIO_H
