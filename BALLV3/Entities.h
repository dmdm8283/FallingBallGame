#pragma once
#ifndef Entity_h
#define Entity_h
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

const int max_entities = 32;

class Entity 
{
public:
	/**
	 * Constructs a new Entity object with the given parameters.
	 *
	 * @param p_x: The initial x-coordinate of the entity.
	 * @param p_y: The initial y-coordinate of the entity.
	 * @param p_text: The SDL_Texture object representing the entity's image.
	 * @param velX: The initial horizontal velocity of the entity (default: 0.0f).
	 * @param velY: The initial vertical velocity of the entity (default: 0.0f).
	 * @param projectile: Indicates whether the entity is a projectile (default: false).
	 * @param hp: The initial health points of the entity (default: 1).
	 * @param is_wall: Indicates whether the entity is a wall (default: false).
	 * @param is_powerUp: Indicates whether the entity is a power-up (default: false).
	 */
	Entity(float p_x, float p_y, SDL_Texture* p_text,
		float velX = 0.0f, float velY = 0.0f,
		bool projectile = false, int hp = 1,
		bool is_wall = false);

	/**
	 * Spawns a new entity based on user input and game conditions.
	 *
	 * This function handles the creation of new entities in the game, such as projectiles or power-ups.
	 * It checks for user input events, verifies the entity count, and determines the entity's initial position
	 * and velocity based on the game state.
	 *
	 * @param event: The SDL_Event object representing the user input event.
	 * @param entities: A reference to the std::vector<Entity> container holding all existing entities in the game.
	 * @param entityTexture: The SDL_Texture object representing the image to be used for the new entity.
	 * @param windowWidth: The width of the game window.
	 * @param windowHeight: The height of the game window.
	 * @param detectOutOfBound: A pointer to a boolean variable indicating whether an entity has gone out of bounds.
	 *
	 * @return void: This function does not return any value.
	 */
	static void Spawn(SDL_Event& event,
		std::vector<Entity>& entities, SDL_Texture* entityTexture,
		int windowWidth, int windowHeight, bool* detectOutOfBound);

	/**
	 * Renders the entity on the specified SDL_Renderer.
	 *
	 * This function uses the entity's texture and current frame rectangle to render the entity on the given SDL_Renderer.
	 * The rendering is done at the entity's current position (x, y) within the game world.
	 *
	 * @param renderer: A pointer to the SDL_Renderer object on which the entity will be rendered.
	 *
	 * @return void: This function does not return any value.
	 */
	void render(SDL_Renderer* renderer);

	/**
	 * Updates the position of the entity based on its current velocity.
	 *
	 * This function calculates the new position of the entity by adding the current velocity components (velocityX and velocityY)
	 * to the entity's current coordinates (x and y). The updated position is then stored in the entity's x and y variables.
	 *
	 * @return void: This function does not return any value.
	 */
	void updatePosition();

	/**
	 * Reduces the entity's health by one point.
	 *
	 * This function decreases the entity's health by one point. If the entity's health reaches zero or below,
	 * the function returns true to indicate that the entity has been defeated. Otherwise, it returns false.
	 *
	 * @return bool: Returns true if the entity's health reaches zero or below, indicating that the entity has been defeated.
	 *               Returns false if the entity's health is still greater than zero.
	 */
	bool takeDamage();

	/**
	 * Retrieves the SDL_Texture object associated with the entity.
	 *
	 * This function returns a pointer to the SDL_Texture object that represents the image
	 * of the entity. The texture is used for rendering the entity on the SDL_Renderer.
	 *
	 * @return SDL_Texture*: A pointer to the SDL_Texture object associated with the entity.
	 */
	SDL_Texture* getTexture();




	//grouping of setter functions
	void setX(float);
	void setY(float);
	void setBaseHealth();

	void setVelocityX(float vx);
	void setVelocityY(float vy);

	void setCollisionDelay(double);
	bool canCollide() const;
	void updateDelay(double);

	void setPositionY(float);
	void setPositionX(float);

	/**
	 * Retrieves the current frame rectangle of the entity.
	 *
	 * This function returns a reference to the SDL_Rect object that represents the current frame
	 * of the entity's animation. The current frame is used to determine which part of the texture
	 * should be rendered on the screen.
	 *
	 * @return SDL_Rect&: A reference to the current frame rectangle of the entity.
	 *                     The returned SDL_Rect object contains the position and dimensions of the current frame.
	 */
	SDL_Rect& getCurrentFrame();
	/**
	 * Retrieves the hitbox rectangle of the entity.
	 *
	 * The hitbox represents the area of the entity that can be collided with other entities.
	 * This function returns a SDL_Rect object that contains the position and dimensions of the hitbox.
	 *
	 * @return SDL_Rect: A SDL_Rect object representing the hitbox of the entity.
	 *                   The returned SDL_Rect object contains the position (x, y) and dimensions (w, h) of the hitbox.
	 *                   The position and dimensions are relative to the game world.
	 */
	SDL_Rect getHitbox() const;

	//grouping of getter functions
	float getX() const;
	float getY() const;
	bool getisProjectile() const;
	bool getIsWall() const;
	float getVelocityY()const;
	float getVelocityX()const;
	int getHealth()const;
	bool getHasCollided() const;
	void setHasCollided(bool);


private:
	bool isWall;
	int baseHealth;
	int health;
	bool hasCollided = false;
	float velocityY;
	float velocityX;
	bool isProjectile;
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* texture;

	double collisionDelay = 0.0f;

};



#endif // Entity_h