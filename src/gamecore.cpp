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

    paddleSpeed = 6;
    paddle = {640/2 - 80/2,480-25,80,25};


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

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
            if(paddle.x <= 0)
                break;
            paddle.x -= paddleSpeed;
            break;
        case SDLK_RIGHT:
            if(paddle.x >= 640-80)
                break;
            paddle.x += paddleSpeed;
            break;
        default:
            break;
        }
    default:
        break;
    }
}

void GameCore::render()
{
    SDL_LockSurface(screen);

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0, 0, 0));

    SDL_FillRect(screen, &paddle, SDL_MapRGB(screen->format,0xFF, 0xFF, 0xFF));

    SDL_UnlockSurface(screen);
    SDL_Flip(screen);
}
