#pragma once
#ifndef Collisions_h
#define Collisions_h
#include "Entities.h"
#include "Player.h"
#include "Entities.h"
#include "Audio.h"

#include <SDL.h>
#include <SDL_image.h>

#include <cmath>
#include <iostream>
#include <vector>

class Entity;
class Player;
class PowerUp;

class Collisions{
public:
    /**
     * Checks for a collision between two SDL_Rect objects.
     *
     * This function determines if two rectangular areas overlap by comparing their positions
     * and dimensions. If the rectangles intersect, the function returns true; otherwise, it
     * returns false.
     *
     * @param rectA A const reference to the first SDL_Rect object to check for collision.
     * @param rectB A const reference to the second SDL_Rect object to check for collision.
     *
     * @return A boolean value indicating whether the two rectangles intersect (true) or not (false).
     */
    static bool contact(const SDL_Rect& rectA, const SDL_Rect& rectB);

    /**
     * Checks for collisions between entities, projectiles, and the player.
     *
     * This function iterates through the given collections of entities and projectiles,
     * and checks for collisions between them and the player. If a collision is detected,
     * the appropriate actions are taken, such as updating the player's health, triggering
     * audio effects, or applying bounce effects to projectiles.
     *
     * @param entities A reference to the collection of entities to check for collisions.
     * @param projectile A reference to the collection of projectiles to check for collisions.
     * @param player A reference to the player entity to check for collisions.
     * @param audio A reference to the audio system to play collision-related audio effects.
     * @param audio3 A reference to the audio system to play additional collision-related audio effects.
     *
     * @return A boolean value indicating whether any collisions were detected (true) or not (false).
     *         The function does not return a specific list of colliding entities or projectiles.
     */
    static bool checkCollisions(std::vector<Entity>& entities, std::vector<Entity>& projectile, Player& player, Audio& audio, Audio& audio3);

    /**
     * Applies a bounce effect to a projectile based on the collision with an entity.
     *
     * This function calculates the new velocity of the projectile after a collision with
     * the given entity. The bounce effect is simulated by reflecting the projectile's
     * velocity across the normal vector of the collision surface.
     *
     * @param projectile A reference to the projectile entity that will be bounced.
     *                   The projectile's velocity will be updated based on the collision.
     * @param entityHitbox A reference to the SDL_Rect representing the hitbox of the entity
     *                    with which the projectile collides. The hitbox is used to calculate
     *                    the collision normal vector.
     *
     * @return This function does not return a value. It modifies the projectile's velocity
     *         directly.
     */
    static void bounceProjectile(Entity& projectile, const SDL_Rect& entityHitbox);

    /**
     * Applies gravity to a collection of projectiles.
     *
     * This function iterates through the given collection of projectiles and updates
     * their y-coordinates based on the provided gravity strength. The function assumes
     * that the projectiles have a velocity component in the y-direction.
     *
     * @param projectiles A reference to the collection of projectiles to which gravity
     *                     will be applied.
     * @param gravityStrength The strength of the gravity force. A positive value
     *                        indicates that the projectiles will accelerate downward,
     *                        while a negative value indicates an upward acceleration.
     *
     * @return This function does not return a value. It modifies the projectiles'
     *         positions directly.
     */
    static void applyGravity(std::vector<Entity>& projectiles, float gravityStrength);

    /**
     * Calculates the impact angle between two entities.
     *
     * @param entityVelocityX The x-component of the velocity of the first entity.
     * @param entityVelocityY The y-component of the velocity of the first entity.
     *
     * @return The impact angle in radians. The angle is calculated based on the
     *         direction of the first entity's velocity relative to the horizontal axis.
     *         The angle is positive for rightward motion and negative for leftward motion.
     *         The angle is in the range [-pi, pi].
     */
    static float calculateImpactAngle(float, float);

private:
};

#endif