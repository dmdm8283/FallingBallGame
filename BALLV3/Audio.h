#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class Audio {
public:
    /**
     * @brief Constructor for the Audio class.
     *
     * The constructor initializes the SDL_mixer audio system and loads the required libraries.
     * It also initializes the sound effects for the "hit", "death", and "level-up" events.
     *
     * @return void
     */
    Audio();
    /**
     * @brief Destructor for the Audio class.
     *
     * The destructor is responsible for cleaning up and freeing the SDL_mixer resources used by the Audio class.
     * It should be called when the game is exiting to free up any allocated memory and close the SDL_mixer audio system.
     *
     * @return void
     */
    ~Audio();

    /**
     * @brief Initializes the SDL_mixer audio system and loads the required libraries.
     *
     * This function initializes the SDL_mixer audio system and loads the required libraries.
     * It should be called before any other audio-related functions can be used.
     *
     * @return true if the SDL_mixer audio system is successfully initialized and the required libraries are loaded; false otherwise.
     */
    bool initialize();

    /**
     * @brief Loads and initializes the sound effects for the game.
     *
     * This function loads the sound effects for the "hit", "death", and "level-up" events.
     * The sound effects are loaded from the specified WAV files.
     *
     * @param hitFilePath The file path to the WAV file containing the "hit" sound effect.
     * @param deathFilePath The file path to the WAV file containing the "death" sound effect.
     * @param levelUpFilePath The file path to the WAV file containing the "level-up" sound effect.
     * @param gOFilePath the file path to WAV file containing game over sound
     * 
     * @return true if the sound effects are successfully loaded and initialized; false otherwise.
     */
    bool loadMp3(const std::string& hitFilePath, const std::string& deathFilePath, const std::string& levelUpFilePath, const std::string& bgFilePath, const std::string& gOFilePath);
    
    /**
     * @brief Plays the hit sound effect.
     *
     * This function plays the sound effect associated with the "hit" event.
     * The sound effect is loaded from the file specified during the initialization
     * of the Audio class.
     *
     * @return void
     */
    void playHitSound();

    /**
     * @brief Plays the death sound effect.
     *
     * This function plays the sound effect associated with the "death" event.
     * The sound effect is loaded from the file specified during the initialization
     * of the Audio class.
     *
     * @return void
     */    
    void playDeathSound();

    /**
     * @brief Plays the level-up sound effect.
     *
     * This function plays the sound effect associated with the "level-up" event.
     * The sound effect is loaded from the file specified during the initialization
     * of the Audio class.
     *
     * @return void
     */
    void playLevelUpSound();

    /**
     * @brief Plays the background music.
     *
     * This function plays the sound effect associated with the "bg" event.
     * The sound effect is loaded from the file specified during the initialization
     * of the Audio class.
     *
     * @return void
     */
    void playBg();

    /**
     * @brief Plays the gameOver sound.
     *
     * This function plays the sound effect associated with the "gameOver" event.
     * The sound effect is loaded from the file specified during the initialization
     * of the Audio class.
     *
     * @return void
     */    
    void playGameOver();

    /**
     * @brief Cleans up and frees the SDL_mixer resources used by the Audio class.
     *
     * This function should be called when the game is exiting to free up any allocated memory and
     * close the SDL_mixer audio system.
     *
     * @return void
     */
    void cleanup();

private:
    Mix_Chunk* hitSound;  
    Mix_Chunk* deathSound; 
    Mix_Chunk* levelUpSound;
    Mix_Chunk* gameOver;
    Mix_Music* bg;
};

#endif // AUDIO_H
