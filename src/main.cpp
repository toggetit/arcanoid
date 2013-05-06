#include <iostream>
#include <cstdlib>
#include "gamecore.hpp"

const uint FRAMERATE = 1000 / 60;

using namespace std;

int main()
{
    GameCore *core = new GameCore();

    if(!core->init())
        return(EXIT_FAILURE);

    //Это будет текущая миллисекунда игры
    uint frameStart = 0;

    while(core->isRunning())
    {
        //Инициализация
        frameStart = SDL_GetTicks();

        SDL_PollEvent(&core->event);

        core->update();

        core->render();

        //Прошло времени
        uint frameDuration = SDL_GetTicks() - frameStart;
        //Если прошло меньше 60 кадров - спим остаток
        if(frameDuration < FRAMERATE)
            SDL_Delay(FRAMERATE - frameDuration);
    }

    core->cleanUp();

    return(EXIT_SUCCESS);
}

