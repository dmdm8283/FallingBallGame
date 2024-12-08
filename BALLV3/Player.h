#pragma once
#ifndef Player_h
#define Player_h
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include <ctime>


#include "Entities.h"
#include "Collisions.h"
#include "Audio.h"


class Player
{
public:
	/**
	 * @brief Constructor for the Player class. Initializes the player's attributes.
	 *
	 * @param width The width of the player's texture.
	 * @param height The height of the player's texture.
	 * @param texture The SDL_Texture representing the player's sprite.
	 * @param windowWidth A reference to the width of the game window.
	 * @param windowHeight A reference to the height of the game window.
	 */
	Player(int width, int height, SDL_Texture* texture, int& windowWidth, int& windowHeight);

	/**
	 * @brief This function handles the player's aiming behavior.
	 *
	 * The aiming function is responsible for managing the player's aiming behavior.
	 * It does not perform any game logic or update the player's position.
	 *
	 * @return This function does not return any value.
	 */
	void aiming() const;

	/**
	 * @brief Renders the player's sprite to the game window.
	 *
	 * This function is responsible for drawing the player's sprite to the game window.
	 * It uses the SDL_Renderer to render the player's texture to the specified position and size.
	 *
	 * @param renderer The SDL_Renderer used for rendering the game graphics.
	 *
	 * @return This function does not return any value.
	 */
	void render(SDL_Renderer* renderer);

	/**
	 * @brief Fires a projectile from the player's position.
	 *
	 * This function creates a new projectile entity and adds it to the projectile vector.
	 * The projectile is positioned at the player's current position and moves with the specified velocity.
	 *
	 * @param projectile A reference to the vector of projectile entities.
	 * @param projectileTexture The SDL_Texture representing the projectile's sprite.
	 * @param velocity The velocity at which the projectile moves.
	 *
	 * @return This function does not return any value.
	 */
	void fireProjectile(std::vector<Entity>& projectile, SDL_Texture* projectileTexture, int velocity) const;

	/**
	 * @brief Handles the player's shooting behavior.
	 *
	 * This function checks for a shooting event (e.g., mouse button click) and fires a projectile
	 * from the player's position if the event occurs. The projectile is added to the projectile vector./
	 *
	 * @param event The SDL_Event object containing the current event.
	 * @param projectile A reference to the vector of projectile entities.
	 * @param projectileTexture The SDL_Texture representing the projectile's sprite.
	 * @param velocity The velocity at which the projectile moves.
	 *
	 * @return This function does not return any value.
	 */
	void shoot(SDL_Event& event, std::vector<Entity>& projectile, SDL_Texture* projectileTexture, int velocity) const;

	/**
	 * @brief Checks if any projectile in the vector has gone out of bounds.
	 *
	 * This function iterates through the projectile vector and checks if any projectile has
	 * gone out of bounds by comparing its position with the window dimensions. If a projectile
	 * is found to be out of bounds, it sets the detectOutOfBounds flag to true and plays an
	 * audio clip.
	 *
	 * @param projectile A reference to the vector of projectile entities.
	 * @param windowWidth A reference to the width of the game window.
	 * @param windowHeight A reference to the height of the game window.
	 * @param detectOutOfBounds A pointer to a boolean flag indicating whether any projectile is out of bounds.
	 * @param audio2 A reference to the Audio object used for playing audio clips.
	 *
	 * @return Returns true if any projectile is found to be out of bounds, otherwise returns false.
	 */
	static bool outOfBounds(std::vector<Entity>& projectile, int& windowWidth, int& windowHeight, bool* detectOutOfBounds, Audio& audio2);

	/**
	 * @brief Retrieves the SDL_Rect representing the player's position and dimensions.
	 *
	 * This function returns a SDL_Rect structure that contains the player's position and dimensions.
	 * The rect's x and y coordinates represent the top-left corner of the player, while the width and height
	 * represent the player's dimensions.
	 *
	 * @return A SDL_Rect structure representing the player's position and dimensions.
	 */
	SDL_Rect getRect() const;

	//grouping of getter functions
	bool getp_OutOfBounds() const;
	float getProjectileX() const;
	float getProjectileY() const;
	float getVelocityX() const;
	float getVelocityY() const;

	//setters for x and y for player
	void setX(int x);
	void setY(int y);

	//update the amount of projectiles per burst every 10 points
	// also play "levelUp sound"
	void updateMaxProj(Audio& audio3);
	//score counter
	//every entity eliminated
	void incrementScore(Audio& audio3);
	int getScore() const;

private:
	int score = 0;
	int maxProjectiles = 2;
	

	bool detectOutOfBounds = false;
	float projectileX;
	float projectileY;
	float velocityX;
	float velocityY;
	SDL_Rect rect;
	SDL_Texture* texture;
};

#endif // !Player_h
#pragma once
