#include "Collisions.h"
#include "Entities.h"

bool Collisions::contact(const SDL_Rect& rectA, const SDL_Rect& rectB)
{

    return SDL_HasIntersection(&rectA, &rectB);
}


bool Collisions::checkCollisions(std::vector<Entity>& entities, std::vector<Entity>& projectiles, Player& player, Audio& audio, Audio& audio3)
{
    bool collisionDetected = false;

    for (auto& projectile : projectiles) {
        projectile.updateDelay(0.0005);
        const SDL_Rect projectileHitbox = projectile.getHitbox();

        for (auto entityIt = entities.begin(); entityIt != entities.end();) {

            const SDL_Rect entityHitbox = entityIt->getHitbox();

            if (!entityIt->getisProjectile() && contact(projectileHitbox, entityHitbox)) {
                projectile.setCollisionDelay(0.0002); 

                float angle = calculateImpactAngle(projectile.getVelocityX(), projectile.getVelocityY());

                bounceProjectile(projectile, entityHitbox);

                projectile.setHasCollided(true);
                audio.playHitSound();

                if (!entityIt-> getIsWall() && entityIt->takeDamage()) {
                    entityIt = entities.erase(entityIt);
                    player.incrementScore(audio3);
                    audio.playGameOver();

                }
                else {
                    ++entityIt;
                }

                collisionDetected = true;
                break;
            }
            else {
                ++entityIt;
            }
        }
    }
    return collisionDetected;
}



/*
*find overlap collision > find dominant axis >
*compares the overlaps (X and Y)  > identify which axis has the smallest intrusion
*resolve X or Y to sit flush with collided entity's edge (usually wall)
*Apply bounce
*/

void Collisions::bounceProjectile(Entity& projectile, const SDL_Rect& entityHitbox) {
    SDL_Rect projectileHitbox = projectile.getHitbox();
    float bounceMultiplier = 0.8f; 

    int overlapX = 0;
    int overlapY = 0;

    //find overlap
    if (projectileHitbox.x + projectileHitbox.w > entityHitbox.x &&
        projectileHitbox.x < entityHitbox.x + entityHitbox.w) {
        overlapX = std::min(projectileHitbox.x + projectileHitbox.w - entityHitbox.x,
            entityHitbox.x + entityHitbox.w - projectileHitbox.x);
    }
    if (projectileHitbox.y + projectileHitbox.h > entityHitbox.y &&
        projectileHitbox.y < entityHitbox.y + entityHitbox.h) {
        overlapY = std::min(projectileHitbox.y + projectileHitbox.h - entityHitbox.y,
            entityHitbox.y + entityHitbox.h - projectileHitbox.y);
    }
    if (overlapX < overlapY) {
        // Horizontal 
        if (projectileHitbox.x + projectileHitbox.w / 2 < entityHitbox.x + entityHitbox.w / 2) {
            // left
            projectile.setPositionX(entityHitbox.x - projectileHitbox.w);
        }
        else {
            // right
            projectile.setPositionX(entityHitbox.x + entityHitbox.w);
        }
        projectile.setVelocityX(-projectile.getVelocityX() * bounceMultiplier);
    }
    else {
        // Vertical 
        if (projectileHitbox.y + projectileHitbox.h / 2 < entityHitbox.y + entityHitbox.h / 2) {
            // above
            projectile.setPositionY(entityHitbox.y - projectileHitbox.h);
        }
        else {
            // below
            projectile.setPositionY(entityHitbox.y + entityHitbox.h);
        }
        projectile.setVelocityY(-projectile.getVelocityY() * bounceMultiplier);
    }
}

void Collisions::applyGravity(std::vector<Entity>& projectiles, float gravityStrength)
{
    for (auto& projectile : projectiles) {
        if (projectile.getisProjectile() && projectile.getHasCollided()) {
            float newVelocityY = projectile.getVelocityY() + gravityStrength;
            projectile.setVelocityY(newVelocityY);
        }
    }
}

float Collisions::calculateImpactAngle(float velocityX, float velocityY)
{
    return atan2(velocityY, velocityX) * 180.0f / M_PI;
}