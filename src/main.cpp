#include <iostream>
#include <cstdlib>
#include "gamecore.hpp"

using namespace std;

int main()
{
    GameCore *core = new GameCore();

    if(!core->init())
        return(EXIT_FAILURE);

    while(core->isRunning())
    {
        SDL_WaitEvent(&core->event);

        core->update();

        core->render();
    }

    core->cleanUp();

    return(EXIT_SUCCESS);
}

