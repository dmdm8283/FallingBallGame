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
	Entity(float p_x, float p_y, SDL_Texture* p_text,
		float velX = 0.0f, float velY = 0.0f,
		bool projectile = false, int hp = 1,
		bool is_wall = false, bool is_powerUp = false);


	static void Spawn(SDL_Event& event,
		std::vector<Entity>& entities, SDL_Texture* entityTexture,
		int windowWidth, int windowHeight, bool* detectOutOfBound);


	void render(SDL_Renderer* renderer);
	void updatePosition();
	bool takeDamage();

	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame() const;
	SDL_Rect getHitbox() const;



	void setVelocityX(float vx);
	void setVelocityY(float vy);

	void setCollisionDelay(double);
	bool canCollide() const;
	void updateDelay(double);

	void setPositionY(float);
	void setPositionX(float);

	float getX();
	float getY();
	bool getisProjectile() const;
	float getVelocityY();
	float getVelocityX();
	int getHealth();
	bool getHasCollided() const;
	void setHasCollided(bool);
	SDL_Rect& getCurrentFrame();
	bool isWall;


	void setX(float);
	void setY(float);
	void setBaseHealth();

private:
	int baseHealth;
	int health;
	bool ispowerUp;
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