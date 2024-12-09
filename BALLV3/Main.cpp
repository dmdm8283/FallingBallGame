#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdio.h>
#include <ctime>

#include "FontManager.h"
#include "Player.h"
#include "Collisions.h"
#include "Entities.h"
#include "RenderWindow.h"
#include "Audio.h"
#include "PowerUp.h"

class Entity;

/*
* death screen with final score and option to press 'q' to quit the screen
* return void
*/
void showDeathScreen(SDL_Renderer* renderer, const std::string& fontID, SDL_Event& event, bool& gameRunning, Player& player, Audio& audio);

int main(int argc, char* args[]) {

    //DATA ABSTRACTION // 
    

    //Image
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0) {
        std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "Image initialization failed: " << SDL_GetError() << std::endl;
    }
    //Font
    if (TTF_Init() == -1) {
        std::cout << "TTF initialization failed: " << TTF_GetError() << std::endl;
    }

    Audio audio;

    // Initialize audio
    if (!audio.initialize()) {
        std::cerr << "Failed to initialize audio: " << Mix_GetError() << std::endl;
    }

    // Load audio files
    if (!audio.loadMp3("hitSound.wav", "deathSound.wav", "levelUpSound.wav", "backgroundMs.wav", "gameOver.wav")) {
        std::cerr << "Failed to load audio files: " << Mix_GetError() << std::endl;
    }

    //max fps
    const int maxFPS = 32;
    const int frame_time = 1000 / maxFPS;
    Uint32 framestart;
    int frame;

    const float gravityStrength = 6.0f;

    srand(static_cast<unsigned int>(time(0)));
    int windowHeight = 840;
    int windowWidth = 620;

    RenderWindow window("window", windowWidth, windowHeight);

    SDL_Texture* blueTexture = window.loadTexture("player.png");
    SDL_Texture* projectileTexture = window.loadTexture("bullet2.png");
    SDL_Texture* backgroundTexture = window.loadTexture("background2.png");

    std::vector<Entity> entities;
    std::vector<Entity> projectile;

    SDL_Surface* mouse = IMG_Load("crosshair.png");
    SDL_Cursor* cursor = SDL_CreateColorCursor(mouse, 0, 0);
    SDL_FreeSurface(mouse);


    Player player(300, 300, blueTexture, windowWidth, windowHeight);

    window.addWalls(entities);

    FontManager::Instance().LoadFont("default", "HomeVideoBold-R90Dv.ttf", 24);


    //textures for entities
    SDL_Texture* planet1 = window.loadTexture("planet1.png");
    SDL_Texture* planet2 = window.loadTexture("planet2.png");
    SDL_Texture* planet3 = window.loadTexture("planet3.png");
    SDL_Texture* planet4 = window.loadTexture("planet4.png");
    SDL_Texture* planet5 = window.loadTexture("planet5.png");

    SDL_Texture* textures[] = { planet1, planet2, planet3, planet4, planet5 };

    static int spawnCounter = 0;

    bool gameRunning = true;
    bool gameOver = false;
    bool restartGame = false;
    SDL_Event event;
    bool isOutOfBounds = false;
    static bool musicStarted = false;


    //PROCESS//
    //GAME LOOP
    while (gameRunning) {
        //max fps
        framestart = SDL_GetTicks();
        frame = SDL_GetTicks() - framestart;
        if (frame < frame_time) {
            SDL_Delay(frame_time - frame);
        }

        //set cursor texture
        SDL_SetCursor(cursor);

        if (!musicStarted) {
            audio.playBg();
            musicStarted = true;
        }

        //Render window
        SDL_RenderClear(window.getRenderer());
        SDL_RenderCopy(window.getRenderer(), backgroundTexture, nullptr, nullptr);


        //Set of static functions that make up the gameloop
        Player::outOfBounds(projectile, windowWidth, windowHeight, &isOutOfBounds, audio);
        
        //entity gets one of the 5 available textures in the textures array
        //selection loops after every 5 spawns.
        SDL_Texture* chosenTexture = textures[spawnCounter % 5];
        Entity::Spawn(event, entities, chosenTexture, windowWidth, windowHeight, &isOutOfBounds);
        spawnCounter++;

        //constantly check for collision betweeen entities and projectiles
        Collisions::checkCollisions(entities, projectile, player, audio, audio);

        //apply gravity on the projectile
        Collisions::applyGravity(projectile, gravityStrength);

        //Score display
        SDL_Color white = { 255, 255, 255 };
        FontManager::Instance().RenderScore("default", white, 60, 20, window.getRenderer(), player);


        //constantly render projectiles, entities, update their position, and allowing shoot operation
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameRunning = false;
            }
            player.shoot(event, projectile, projectileTexture, 32);
        }

        for (auto& proj : projectile) {
            proj.updatePosition();
        }

        for (auto& proj : projectile) {
            window.render(proj);
        }
        for (auto& entity : entities) {
            window.render(entity);
        }

        //game over 
        for (auto& entity : entities) {
            if (entity.getY() <= -48 && !entity.getisProjectile() && !entity.getIsWall()) {
                gameRunning = false; // Stop the game loop
                break;
            }
        }
        player.render(window.getRenderer());



        window.display();

        //close the game window
        if (!gameRunning) {
            window.cleanUp();
            SDL_DestroyRenderer(window.getRenderer());
            SDL_DestroyWindow(window.getWindow());
            SDL_Window* gameOverWindow = SDL_CreateWindow(
                "Game Over",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                620, 840,
                SDL_WINDOW_SHOWN
            );
            SDL_Renderer* gameOverRenderer = SDL_CreateRenderer(gameOverWindow, -1, SDL_RENDERER_ACCELERATED);

            showDeathScreen(gameOverRenderer, "default", event, gameRunning, player, audio);

            SDL_DestroyRenderer(gameOverRenderer);
            SDL_DestroyWindow(gameOverWindow);

            break;
        }

    }

    //Cleanup
    SDL_DestroyTexture(backgroundTexture);
    FontManager::Instance().CleanUp();
    audio.cleanup();
    window.cleanUp();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}

void showDeathScreen(SDL_Renderer* renderer, const std::string& fontID, SDL_Event& event, bool& gameRunning, Player& player, Audio& audio) {
    SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "background2.png");
    if (!backgroundTexture) {
        std::cerr << "Failed to load background texture: " << SDL_GetError() << std::endl;
        return;
    }

    // Render the background
    SDL_RenderClear(renderer); 
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

    // Render the text
    SDL_Color white = { 255, 255, 255 };
    FontManager::Instance().RenderText(fontID, "Game Over", white, 190, 300, renderer);
    FontManager::Instance().RenderText(fontID, "Press Q to Quit", white, 180, 400, renderer);
    FontManager::Instance().RenderText(fontID, "Final Score:", white, 180, 500, renderer);
    FontManager::Instance().RenderText(fontID, std::to_string(player.getScore()), white, 350, 500, renderer);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(backgroundTexture);

    audio.playGameOver();
    
    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT ||
                (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)) {
                gameRunning = false;
                return;
            }
        }
    }
}