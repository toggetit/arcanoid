#include "gamecore.hpp"
#include <iostream>
#define BALL_SIDE 20
#define PADDLE_W 80
#define PADDLE_H 25
#define BALLSPEED 4

GameCore::GameCore()
{
}

GameCore::~GameCore() {
  std::cout<<"Destructor called"<<std::endl;
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(window);
  
}

bool GameCore::init()
{
  if(SDL_Init(SDL_INIT_EVERYTHING))
        return false;

    window = SDL_CreateWindow("Arcanoid!",
			      SDL_WINDOWPOS_UNDEFINED,
			      SDL_WINDOWPOS_UNDEFINED,
			      640,
			      480,
			      SDL_WINDOW_SHOWN);
    
    if(window == NULL) {
      std::cout<<"Can't create window "<<SDL_GetError();
      return false;
    }

    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(ren == NULL) {
      std::cout<<"Can't create renderer "<<SDL_GetError();
      SDL_DestroyWindow(window);
      return false;
    }
    
    running = true;

    reset();

    return true;
}

void GameCore::reset()
{
    paddleSpeed = 6;
    paddle = {640/2 - PADDLE_W/2, 480 - PADDLE_H, PADDLE_W, PADDLE_H};
    //paddle = {100, 100, PADDLE_W, PADDLE_H};

    ballSpeed = 4;
    //ball = {paddle.x + paddle.w/2 - BALL_SIDE/2, paddle.y - BALL_SIDE, BALL_SIDE, BALL_SIDE};
    ball = {0, 0, BALL_SIDE, BALL_SIDE};
    ballLaunched = false;

    std::cout<<ball.x<<" "<<ball.y<<" "<<paddle.x<<" "<<paddle.y<<std::endl;
}

void GameCore::update()
{
  //std::cout<<"Called update()"<<std::endl;
  
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

    if(collisionDetection(paddle, ball))
    {
        if((x > 0) && (y > 0))
        {
            x = -x;
            //y = -y;
        }
        if((x < 0) && (y > 0))
        {
            y = -y;
        }
        else
        {
            x = -x;
            y = -y;
        }


        ball.x += x;
        ball.y += y;

        std::cout<<"DETECT"<<std::endl;
        return;
    }

    calculations();

  
}

void GameCore::calculations()
{
  //std::cout<<"Called calculations()"<<std::endl;
    /*
    if(!ballLaunched)
    {
        ball.x = paddle.x + paddle.w/2 - BALL_SIDE/2;
        ball.y = paddle.y - BALL_SIDE;
        return;
    }
    */


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

bool GameCore::collisionDetection(SDL_Rect &A, SDL_Rect &B) const
{
    //The sides of the rectangles
    int leftA, leftB; int rightA, rightB;
    int topA, topB; int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if(( bottomA <= topB ) || ( topA >= bottomB ) ||
    ( rightA <= leftB ) || ( leftA >= rightB )) return false;
    //If none of the sides from A are outside B
    return true;
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
  
  //SDL_RenderClear(ren);

  //Backgrouund
  SDL_SetRenderDrawColor( ren, 0, 0, 0, 255 );
  SDL_RenderClear(ren);
  //old background
  //SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0, 0, 0));

  //draw paddle
  SDL_SetRenderDrawColor( ren, 0, 255, 0, 255 );
  SDL_RenderDrawRect(ren, &paddle);
  //old paddle
  //SDL_FillRect(screen, &paddle, SDL_MapRGB(screen->format,0xFF, 0xFF, 0xFF));

  //draw ball
  SDL_SetRenderDrawColor( ren, 0, 255, 0, 255 );
  SDL_RenderDrawRect(ren, &ball);
  //old ball
  //SDL_FillRect(screen, &ball, SDL_MapRGB(screen->format,0xFF, 0x11, 0xFF));
    
  SDL_RenderPresent(ren);
  
}
