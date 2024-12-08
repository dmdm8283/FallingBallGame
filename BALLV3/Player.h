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
	Player(int width, int height, SDL_Texture* texture, int& windowWidth, int& windowHeight);

	void aiming() const;
	void render(SDL_Renderer* renderer);

	void fireProjectile(std::vector<Entity>& projectile, SDL_Texture* projectileTexture, int velocity) const;
	void shoot(SDL_Event& event, std::vector<Entity>& projectile, SDL_Texture* projectileTexture, int velocity) const;	
	bool outOfBounds(std::vector<Entity>& projectile, int& windowWidth, int& windowHeight, bool* detectOutOfBounds, Audio& audio2) const;

	SDL_Rect getRect() const;

	
	bool getp_OutOfBounds() const;
	float getProjectileX() const;
	float getProjectileY() const;
	float getVelocityX() const;
	float getVelocityY() const;


	void setX(int x);
	void setY(int y);

	void updateMaxProj(Audio& audio3);
	void incrementScore(Audio& audio3);
	int getScore() const;
	void resetPlayer();

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
