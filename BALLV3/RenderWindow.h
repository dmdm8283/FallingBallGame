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
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void display();
	SDL_Window* getWindow() const { return window; }
	SDL_Renderer* getRenderer() const { return renderer; }

	void addWalls(std::vector<Entity>& entities) const;


private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* wallTexture;

	Entity leftWall;
	Entity rightWall;
};

#endif // !RENDERWINDOW_H
