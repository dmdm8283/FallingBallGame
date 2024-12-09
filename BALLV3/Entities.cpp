#include "Entities.h"
//ENTITIES 

Entity::Entity(float p_x, float p_y, SDL_Texture* p_text, float velX, float velY, bool projectile, int hp, bool is_wall)
    : x(p_x), y(p_y), texture(p_text), velocityX(velX), velocityY(velY), isProjectile(projectile), health(hp), isWall(is_wall)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    if (isProjectile) {
        currentFrame.w = 32;
        currentFrame.h = 32;
    }
    else if (isWall) {
        currentFrame.w = 50;
        currentFrame.h = 840;

    }
    else {
        currentFrame.w = 64;
        currentFrame.h = 64;
    }
}



bool Entity::takeDamage()
{
    if (health > 0) {
        health -= 1;
    }
    return health <= 0;

}


void Entity::updatePosition() {
    if (isProjectile) {
        y += velocityY;
        x += velocityX;
    }
}


void Entity::render(SDL_Renderer* renderer)
{
    SDL_Rect destRect = {
        static_cast<int>(x),
        static_cast<int>(y),
        currentFrame.w,
        currentFrame.h
    };
    SDL_RenderCopy(renderer, texture, &currentFrame, &destRect);
}


void Entity::Spawn(SDL_Event& event, std::vector<Entity>& entities, SDL_Texture* entityTexture, int windowWidth, int windowHeight, bool* detectOutOfBound)
{
    static int entitiesToSpawn = 3;
    static int placeholder = 2;
    static bool initialSpawn = false;
    static int entityHealth = 2; 

    int spawnWidth = windowWidth - 128;
    int spawnHeight = windowHeight / 6 - 64;
    float minimumDistance = 128.0f;
    int maxAttempts = 10;

    static bool toggleSpawn = false;

    /* Check spawning location spaced out
       If it doesn't find any (after 10 tries), spawn randomly */

    if (!initialSpawn)
    {
        for (int i = 0; i < 3; i++)
        {
            float randomX, randomY;
            bool positionFound = false;
            int attempts = 0;   

            while (!positionFound && attempts < maxAttempts) {
                randomX = static_cast<float>(rand() % spawnWidth);
                randomY = static_cast<float>(windowHeight - spawnHeight - (rand() % spawnHeight));
                positionFound = true;

                for (const auto& entity : entities) {
                    float dx = entity.x - randomX;
                    float dy = entity.y - randomY;
                    if (std::sqrt(dx * dx + dy * dy) < minimumDistance) {
                        positionFound = false;
                        break;
                    }
                }
                attempts++;
            }

            if (!positionFound && !entities.empty()) {
                randomX = static_cast<float>(rand() % spawnWidth);
                randomY = static_cast<float>(windowHeight - spawnHeight - (rand() % spawnHeight));
            }

            entities.emplace_back(randomX, randomY, entityTexture, 0.0f, 0.0f, false, entityHealth);
        }
        initialSpawn = true;
    }
    if (*detectOutOfBound && toggleSpawn)
    {
        toggleSpawn = false;
        for (int i = 0; i < entitiesToSpawn; ++i)
        {
            float randomX, randomY;
            bool positionFound = false;
            int attempts = 0;

            while (!positionFound && attempts < maxAttempts) {
                randomX = static_cast<float>(rand() % spawnWidth);
                randomY = static_cast<float>(windowHeight + (rand() % spawnHeight));
                positionFound = true;

                for (const auto& entity : entities) {
                    float dx = entity.x - randomX;
                    float dy = entity.y - randomY;
                    if (std::sqrt(dx * dx + dy * dy) < minimumDistance) {
                        positionFound = false;
                        break;
                    }
                }
                attempts++;
            }

            if (!positionFound && !entities.empty()) {
                randomX = static_cast<float>(rand() % spawnWidth);
                randomY = static_cast<float>(windowHeight + spawnHeight - (rand() % spawnHeight));
            }

            entities.emplace_back(randomX, randomY, entityTexture, 0.0f, 0.0f, false, entityHealth);
        }

        if (placeholder % 5 == 0) {
            entitiesToSpawn++;
            entityHealth++; 
        }
        placeholder++;

        for (auto& entity : entities)
        {
            if (!entity.isProjectile && !entity.isWall)
            {
                entity.y -= 128.0f;
            }
        }
    }
    else if (*detectOutOfBound)
    {
        toggleSpawn = true; // Enable spawning for the next call
    }

}


void Entity::setCollisionDelay(double delay)
{
    collisionDelay = delay;
}

bool Entity::canCollide() const
{
    return collisionDelay <= 0;
}

void Entity::updateDelay(double time)
{
    if (collisionDelay > 0.0f)
    {
        collisionDelay -= time;
    }
}

void Entity::setPositionX(float newX)
{
    x = newX;
}

void Entity::setPositionY(float newY)
{
    y = newY;
}

SDL_Rect Entity::getHitbox() const
{
    SDL_Rect rect;
    if (isProjectile)
    {
        rect.x = static_cast<int>(x);
        rect.y = static_cast<int>(y);
        rect.w = currentFrame.w;
        rect.h = currentFrame.h;
        
    }
    else {
        rect.x = static_cast<int>(x);
        rect.y = static_cast<int>(y);
        rect.w = currentFrame.w + 10; //KEEP AT 10 to avoid jittering
        rect.h = currentFrame.h;
    }
    return rect;

}

void Entity::setVelocityX(float vx) {
    velocityX = vx;
}

void Entity::setVelocityY(float vy) {
    velocityY = vy;
}



float Entity::getX()const
{
    return x;
}

float Entity::getY()const
{
    return y;
}

bool Entity::getisProjectile() const
{
    return isProjectile;

}

bool Entity::getIsWall() const
{
    return isWall;
}

float Entity::getVelocityY()const
{
    return velocityY;
}
float Entity::getVelocityX()const
{
    return velocityX;
}
int Entity::getHealth()const
{
    return health;
}

SDL_Texture* Entity::getTexture()
{
    return texture;
}


bool Entity::getHasCollided() const {
    return hasCollided;
}

void Entity::setHasCollided(bool state) {
    hasCollided = state;
}
SDL_Rect& Entity::getCurrentFrame() {
    return currentFrame;
}

void Entity::setX(float newX) {
    x = newX;
}

void Entity::setY(float newY) {
    y = newY;
}


void Entity::setBaseHealth()
{
    baseHealth = health;
}
