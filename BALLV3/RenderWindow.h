#pragma once
#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Entities.h"

class RenderWindow
{
public:
	/**
	 * Constructor that initializes an SDL window and renderer.
	 *
	 * This function sets up the SDL window with the specified title, width, and height,
	 * and creates an associated renderer for rendering content.
	 *
	 * @param p_title A pointer to a C-string representing the title of the window.
	 * @param p_w The width of the window in pixels.
	 * @param p_h The height of the window in pixels.
	 */
	RenderWindow(const char* p_title, int p_w, int p_h);

	/**
	 * Loads a texture from the specified file path.
	 *
	 * This function loads an image file and converts it into an SDL_Texture, which
	 * can be used for rendering in the SDL context.
	 *
	 * @param p_filePath A pointer to a C-string representing the path to the image file.
	 *
	 * @return A pointer to the SDL_Texture object if loading is successful, or nullptr if it fails.
	 */
	SDL_Texture* loadTexture(const char* p_filePath);

	/**
	 * Cleans up and frees resources associated with the SDL window and renderer.
	 *
	 * This function destroys the window and renderer created by the RenderWindow
	 * object to free allocated memory and prevent resource leaks.
	 */
	void cleanUp();

	/**
	 * Clears the current rendering target.
	 *
	 * This function resets the rendering target, preparing it for a new frame.
	 * Typically used at the start of a rendering cycle.
	 */
	void clear();

	/**
	 * Renders an entity onto the screen.
	 *
	 * This function takes an `Entity` object and uses its position and texture
	 * to draw it onto the rendering target.
	 *
	 * @param p_entity A reference to the `Entity` object to be rendered.
	 */
	void render(Entity& p_entity);

	/**
	 * Displays the rendered content on the screen.
	 *
	 * This function presents the back buffer (the current rendering target) to the screen,
	 * effectively updating the displayed image.
	 */
	void display();

	/**
	 * Retrieves the SDL window associated with this object.
	 *
	 * This function returns a pointer to the SDL window, allowing access to its properties
	 * and functions.
	 *
	 * @return A pointer to the SDL_Window object.
	 */
	SDL_Window* getWindow() const { return window; }

	/**
	 * Retrieves the SDL renderer associated with this object.
	 *
	 * This function returns a pointer to the SDL renderer, which is used for rendering
	 * content to the window.
	 *
	 * @return A pointer to the SDL_Renderer object.
	 */
	SDL_Renderer* getRenderer() const { return renderer; }

	/**
	 * Adds wall entities to a provided vector for rendering and interaction.
	 *
	 * This function creates wall objects and appends them to the provided vector,
	 * enabling their inclusion in the game world for rendering and collision detection.
	 *
	 * @param entities A reference to a vector of `Entity` objects to which the walls will be added.
	 */
	void addWalls(std::vector<Entity>& entities) const;


private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* wallTexture;

	Entity leftWall;
	Entity rightWall;
};

#endif // !RENDERWINDOW_H
