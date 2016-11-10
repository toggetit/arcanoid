#ifndef GAMECORE_H
#define GAMECORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

class GameCore
{
public:
  GameCore();
  ~GameCore();

  bool init();
  void update();
  void render();
  bool isRunning() {return running;}

  SDL_Event event;

private:
  SDL_Window *window;
  SDL_Renderer* ren;
  SDL_Surface* surf;
  bool running;

  SDL_Rect ball;
  void startBall();
  bool ballLaunched;
  short int unsigned ballSpeed;
  int x, y;   //Вектор движения

  void reset();

  bool collisionDetection(SDL_Rect &A, SDL_Rect &B) const;

  void calculations();

  uint paddleSpeed;
  SDL_Rect paddle;

};

#endif // GAMECORE_H
