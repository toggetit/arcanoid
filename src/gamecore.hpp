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

    uint paddleSpeed;
    SDL_Rect paddle;

};

#endif // GAMECORE_H
