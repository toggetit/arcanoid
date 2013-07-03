#ifndef GAMECORE_H
#define GAMECORE_H

#include <SDL/SDL.h>

class GameCore
{
public:
    GameCore();

    bool init();
    void cleanUp();
    void update();
    void render();
    bool isRunning() {return running;}

    SDL_Event event;

private:
    SDL_Surface *screen;
    bool running;

    SDL_Rect ball;
    void startBall();
    bool ballLaunched;
    short int unsigned ballSpeed;
    int x, y;

    void reset();

    bool collisionDetection(SDL_Rect &obj, SDL_Rect &ball) const;

    void calculations();

    uint paddleSpeed;
    SDL_Rect paddle;

};

#endif // GAMECORE_H
