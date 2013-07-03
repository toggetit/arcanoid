#include "gamecore.hpp"
#define BALL_SIDE 20
#define PADDLE_W 80
#define PADDLE_H 25
#include <iostream>

GameCore::GameCore()
{
}

bool GameCore::init()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_TIMER))
        return false;

    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWACCEL | SDL_DOUBLEBUF);
    running = true;

    reset();

    return true;
}

void GameCore::reset()
{
    paddleSpeed = 6;
    paddle = {640/2 - PADDLE_W/2, 480 - PADDLE_H, PADDLE_W, PADDLE_H};

    ballSpeed = 4;
    ball = {paddle.x + paddle.w/2 - BALL_SIDE/2, paddle.y - BALL_SIDE, BALL_SIDE, BALL_SIDE};
    ballLaunched = false;
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
        case SDLK_SPACE:
            startBall();
            break;
        default:
            break;
        }
    default:
        break;
    }

    calculations();

    if(collisionDetection(paddle, ball))
    {
        std::cout<<"DETECT"<<std::endl;
        return;
    }
}

void GameCore::calculations()
{
    if(!ballLaunched)
    {
        ball.x = paddle.x + paddle.w/2 - BALL_SIDE/2;
        ball.y = paddle.y - BALL_SIDE;
        return;
    }



    if((ball.x <= 0) || ball.x >= (640 - BALL_SIDE)) x = -x;
    if(ball.y <= 0) y = -y;

    if(ball.y >= (480 - BALL_SIDE))
    {
        reset();
        return;
    }


    ball.x += x;
    ball.y += y;

}

bool GameCore::collisionDetection(SDL_Rect &obj, SDL_Rect &ball) const
{
    if(!ballLaunched) return false;

    if (((ball.x + BALL_SIDE - 5) >= obj.x) || ((ball.y + BALL_SIDE - 5) >= obj.y)) return true;
    return false;
}


void GameCore::startBall()
{
    if(ballLaunched)return;

    x = -ballSpeed;
    y = -ballSpeed;
    ballLaunched = true;
}

void GameCore::render()
{
    SDL_LockSurface(screen);

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0, 0, 0));

    SDL_FillRect(screen, &paddle, SDL_MapRGB(screen->format,0xFF, 0xFF, 0xFF));

    SDL_FillRect(screen, &ball, SDL_MapRGB(screen->format,0xFF, 0x11, 0xFF));

    SDL_UnlockSurface(screen);
    SDL_Flip(screen);
}
