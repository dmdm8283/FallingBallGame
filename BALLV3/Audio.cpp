#include "Audio.h"
#include <iostream>

Audio::Audio() : hitSound(nullptr), deathSound(nullptr), levelUpSound(nullptr) {}

Audio::~Audio() {
    cleanup();
}

bool Audio::initialize() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Audio initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Mixer initialization failed: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

bool Audio::loadMp3(const std::string& hitFilePath, const std::string& deathFilePath, const std::string& levelUpFilePath, const std::string& ostFilePath) {
    hitSound = Mix_LoadWAV(hitFilePath.c_str());
    deathSound = Mix_LoadWAV(deathFilePath.c_str());
    levelUpSound = Mix_LoadWAV(levelUpFilePath.c_str());
    ost = Mix_LoadMUS(ostFilePath.c_str());

    if (!hitSound) {
        std::cerr << "Failed to load hit sound: " << Mix_GetError() << std::endl;
        return false;
    }
    if (!deathSound) {
        std::cerr << "Failed to load death sound: " << Mix_GetError() << std::endl;
        return false;
    }
    if (!levelUpSound) {
        std::cerr << "Failed to load level-up sound: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

void Audio::playOst()
{
    if (ost) {
        Mix_PlayMusic(ost, -1); 
    }
    else {
        std::cerr << "OST is not loaded." << std::endl;
    }
}

void Audio::playHitSound() {
    if (hitSound) {
        Mix_PlayChannel(-1, hitSound, 0);
    }
    else {
        std::cerr << "Hit sound no good" << std::endl;
    }
}

void Audio::playDeathSound() {
    if (deathSound) {
        Mix_PlayChannel(-1, deathSound, 0);
    }
    else {
        std::cerr << "Death sound no good" << std::endl;
    }
}

void Audio::playLevelUpSound() {
    if (levelUpSound) {
        Mix_PlayChannel(-1, levelUpSound, 0);
    }
    else {
        std::cerr << "Level-up sound no good" << std::endl;
    }
}

void Audio::cleanup() {
    if (hitSound) {
        Mix_FreeChunk(hitSound);
        hitSound = nullptr;
    }
    if (deathSound) {
        Mix_FreeChunk(deathSound);
        deathSound = nullptr;
    }
    if (levelUpSound) {
        Mix_FreeChunk(levelUpSound);
        levelUpSound = nullptr;
    }

    Mix_CloseAudio();
    SDL_Quit();
}
