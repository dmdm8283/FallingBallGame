#include "RenderWindow.h"
#include "Entities.h"  

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h) 
    : window(NULL), renderer(NULL), wallTexture(NULL),
    leftWall(0, 0, nullptr, 0.0f, 0.0f, false, INT_MAX),
    rightWall(p_w - 50, 0, nullptr, 0.0f, 0.0f, false, INT_MAX) 
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cout << "WINDOW ERROR: " << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    wallTexture = loadTexture("wall.png");
    if (!wallTexture) {
        std::cout << "PROBLEM with WALL" << std::endl;
    }

    leftWall = Entity(0, 0, wallTexture, 0.0f, 0.0f, false, INT_MAX, true);
    rightWall = Entity(p_w - 50, 0, wallTexture, 0.0f, 0.0f, false, INT_MAX, true);

    leftWall.getCurrentFrame().h = p_h; 
    rightWall.getCurrentFrame().h = p_h;

}


void RenderWindow::addWalls(std::vector<Entity>& entities) const
{
    entities.insert(entities.begin(), leftWall);
    entities.insert(entities.begin() + 1, rightWall);
}

void RenderWindow::render(Entity& p_entity)
{
    SDL_Rect src;
    src.x = static_cast<int>(p_entity.getCurrentFrame().x);
    src.y = static_cast<int>(p_entity.getCurrentFrame().y);
    src.w = static_cast<int>(p_entity.getCurrentFrame().w);
    src.h = static_cast<int>(p_entity.getCurrentFrame().h);

    SDL_Rect dst;
    dst.x = static_cast<int>(p_entity.getX());
    dst.y = static_cast<int>(p_entity.getY());
    dst.w = p_entity.getCurrentFrame().w;
    dst.h = p_entity.getCurrentFrame().h;

    SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dst);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);
    if (texture == NULL)
    {
        std::cout << "MERDE TEXTURE : " << IMG_GetError() << std::endl;

    }
    return texture;
}
void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}


void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}
