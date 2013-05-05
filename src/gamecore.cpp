#include "gamecore.hpp"

GameCore::GameCore()
{
}

bool GameCore::init()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_TIMER))
        return false;

    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWACCEL | SDL_DOUBLEBUF);
    running = true;

    return true;
}

void GameCore::cleanUp()
{
    SDL_Quit();
}

void GameCore::update()
{
    switch (event.type) {
    case SDL_QUIT:
        running = false;
        break;
    default:
        break;
    }
}

void GameCore::render()
{

}
