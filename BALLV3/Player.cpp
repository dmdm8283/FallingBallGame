#include "Player.h"
Player::Player(int width, int height, SDL_Texture* texture, int& windowWidth, int& windowHeight)
	:texture(texture)
{
	rect = { 0, 0, 64, 64 };
	rect.x = (windowWidth / 2) - (rect.w / 2);
	rect.y = 64;
}

void Player::aiming() const
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	int playerCenterX = rect.x + rect.w / 2;
	int playerCenterY = rect.y + rect.h / 2;

	double deltaX = mouseX - playerCenterX;
	double deltaY = mouseY - playerCenterY;
	double angle = atan2(deltaY, deltaX) * 180 / M_PI;
}

void Player::fireProjectile(std::vector<Entity>& projectile, SDL_Texture* projectileTexture, int velocity) const
{
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	int playerCenterX = rect.x + rect.w / 2 - 15; //centered shooting
	int playerCenterY = rect.y + rect.h / 2;

	double deltaX = mouseX - playerCenterX;
	double deltaY = mouseY - playerCenterY;
	double angle = atan2(deltaY, deltaX);

	int projectileX = playerCenterX;
	int projectileY = playerCenterY;

	int velocityX = velocity * cos(angle);
	int velocityY = velocity * sin(angle);


	projectile.emplace_back(projectileX, projectileY, projectileTexture, velocityX, velocityY, true);
	//std::cout << projectile.size() << std::endl;

}

/*
press space > shoot > wait 0.09 > shoot again until firedProjectile >= maxProjectile
keep fireDelay low to hide inconsistency errors
SDL_Delay() and SDL_Getticks() doesn't work
delay makes everything shoot at once, i cant fix it (if can fix that then use delay cuz its consistent)
SDL_Getticks is stupidly inconsistent unless change FPS (don't do that)
*/

void Player::shoot(SDL_Event& event, std::vector<Entity>& projectiles, SDL_Texture* projectileTexture, int velocity) const
{
	static bool isFiring = false;
	static int firedProjectiles = 0;
	static clock_t lastFireTime = 0;

	const double fireDelay = 0.09;
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && !isFiring)
	{
		isFiring = true;
		firedProjectiles = 0;
		lastFireTime = clock();
		fireProjectile(projectiles, projectileTexture, velocity); 
		firedProjectiles++;
	}

	if (isFiring)
	{
		clock_t currentTime = clock();
		double elapsedTime = double(currentTime - lastFireTime) / CLOCKS_PER_SEC;

		if (elapsedTime >= fireDelay)
		{
			fireProjectile(projectiles, projectileTexture, velocity);
			firedProjectiles++;
			lastFireTime = currentTime; 

			if (firedProjectiles >= maxProjectiles)
			{
				isFiring = false; 
			}
		}
	}
}





bool Player::outOfBounds(std::vector<Entity>& projectile, int& windowWidth, int& windowHeight, bool* detectOutOfBounds, Audio& audio2)
{
	*detectOutOfBounds = false;

	for (auto it = projectile.begin(); it != projectile.end(); )
	{
		if (it->getX() < 0 || it->getX() > windowWidth || it->getY() < 0
			|| it->getY() > windowHeight || it->getY() < 64)
		{
			it = projectile.erase(it);
			*detectOutOfBounds = true;
			audio2.playDeathSound();
			//std::cout << "Projectiles remaining: " << projectile.size() << "\n";

		}
		else {
			++it;
		}
	}
	return *detectOutOfBounds;
}


void Player::setX(int x) { rect.x = x; }
void Player::setY(int y) { rect.y = y; }

void Player::updateMaxProj(Audio& audio3) {
	if (score % 10 == 0 && score != 0) {
		maxProjectiles++;
		audio3.playLevelUpSound();
		//std::cout << "Max projectiles: " << maxProjectiles << std::endl;
	}
}
void Player::incrementScore(Audio& audio3) {
	updateMaxProj(audio3);
	score += 1;
}

int Player::getScore() const {
	return score;
}

void Player::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

SDL_Rect Player::getRect() const
{
	return rect;
}

bool Player::getp_OutOfBounds() const
{
	return detectOutOfBounds;
}

float Player::getProjectileX() const
{
	return projectileX;
}

float Player::getProjectileY() const
{
	return projectileY;
}

float Player::getVelocityX() const
{
	return velocityX;
}

float Player::getVelocityY() const
{
	return velocityY;
}
