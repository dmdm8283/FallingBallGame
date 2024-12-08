#pragma once
#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <map>
#include "Player.h"
class FontManager {
public:
    /**
     * @brief Provides a singleton instance of the FontManager class for managing fonts.
     *
     * This class is responsible for loading, rendering, and cleaning up fonts using SDL_ttf library.
     * It provides methods to load fonts, render text, render player scores, and clean up resources.
     *
     * @return A reference to the singleton instance of FontManager.
     */
    static FontManager& Instance();

    /**
     * @brief Loads a font from the specified file and stores it in the font manager.
     *
     * This function uses SDL_ttf library to load a font from the given file path.
     * The loaded font is stored in the font manager with the given fontID for later use.
     *
     * @param fontID A unique identifier for the font.
     * @param path The file path of the font file.
     * @param fontSize The size of the font in pixels.
     *
     * @return True if the font was successfully loaded and stored in the font manager, false otherwise.
     */
    bool LoadFont(const std::string& fontID, const std::string& path, int fontSize);

    /**
     * @brief Renders the specified text using the loaded font and color at the given position.
     *
     * This function uses the loaded font with the given fontID and renders the specified text
     * using the provided color at the given position (x, y) on the SDL_Renderer.
     *
     * @param fontID The unique identifier of the font to be used for rendering.
     * @param text The text to be rendered.
     * @param color The color of the text.
     * @param x The x-coordinate of the position where the text will be rendered.
     * @param y The y-coordinate of the position where the text will be rendered.
     * @param renderer The SDL_Renderer on which the text will be rendered.
     */
    void RenderText(const std::string& fontID, const std::string& text, SDL_Color color, int x, int y, SDL_Renderer* renderer);

    /**
     * @brief Renders the player's score using the loaded font and color at the given position.
     *
     * This function uses the loaded font with the given fontID and renders the player's score
     * using the provided color at the given position (x, y) on the SDL_Renderer.
     * The score is only rendered if it has changed since the last call to this function.
     *
     * @param fontID The unique identifier of the font to be used for rendering.
     * @param color The color of the score text.
     * @param x The x-coordinate of the position where the score will be rendered.
     * @param y The y-coordinate of the position where the score will be rendered.
     * @param renderer The SDL_Renderer on which the score will be rendered.
     * @param player The reference to the Player object whose score needs to be rendered.
     */
    void RenderScore(const std::string& fontID, SDL_Color color, int x, int y, SDL_Renderer* renderer, Player& player);

    /**
     * @brief Cleans up and frees all resources associated with the FontManager.
     *
     * This function iterates through the loaded fonts, frees each TTF_Font using TTF_CloseFont,
     * and clears the font map. It also destroys the cached score texture if it exists.
     * This function should be called when the application is exiting to free up resources.
     */
    void CleanUp();


private:
    FontManager() = default;
    ~FontManager() = default;
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;
    int lastScore = -1;
    SDL_Texture* cachedScoreTexture = nullptr;
    std::map<std::string, TTF_Font*> fonts;
};

#endif // FONTMANAGER_H
