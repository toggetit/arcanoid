#ifndef GAMECORE_H
#define GAMECORE_H

#include <SDL/SDL.h>

const int FRAMES_PER_SECOND = 20;

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

};

#endif // GAMECORE_H
