
#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Score.h"
using namespace std;
const int SCREEN_WIDTH = 576*2;
const int SCREEN_HEIGHT = 324*2;
const int PIPE_WIDTH = 100;
const int PIPE_HEIGHT = 1400;
const int PIPE_GAP = 1600;
const int PIPE_SPEED = 1;
const int PIPE_SPAWN_X = SCREEN_WIDTH + 50;
const int PIPE_SPAWN_INTERVAL = 390;
const int PIPE_SPAWN_INTERVAL_2 = 360;
const int PIPE_SPAWN_INTERVAL_3 = 340;
//Gia tri cua ong nuoc tren**********************************************************
const int topPipeYValues[] = {-550, 230, 100, 600};


class Pipe {
public:
    SDL_FRect rect;
    bool isTop;
    bool scored;
    Pipe(int x, int y, bool top);
    void move();
    void render(SDL_Renderer* renderer, SDL_Texture* texture);

};

class PipeManager {
public:
    vector<Pipe> pipes;
    SDL_Texture* topPipeTexture;
    SDL_Texture* bottomPipeTexture;
    int spawnTimer;
    bool pairScored;

    PipeManager(SDL_Texture* topTex, SDL_Texture* bottomTex);
    void addPipe();
    void update();
    void update2();
    void update3();
    void render(SDL_Renderer* renderer);
};
#endif
