#include "Object.h"
#include <algorithm>
#include <iostream>
using namespace std;
Pipe::Pipe(int x, int y, bool top) {
    rect.x = (float)x;
    rect.y = (float)y;
    rect.w = (float)PIPE_WIDTH;
    rect.h = (float)PIPE_HEIGHT;
    isTop = top;
    scored = false;
}

void Pipe::move() {
    rect.x -= PIPE_SPEED;
}

void Pipe::render(SDL_Renderer* renderer, SDL_Texture* texture) {
    SDL_Rect intRect;
    intRect.x = (int)rect.x;
    intRect.y = (int)rect.y;
    intRect.w = (int)rect.w;
    intRect.h = (int)rect.h;
    SDL_RenderCopy(renderer, texture, NULL, &intRect);
}

PipeManager::PipeManager(SDL_Texture* topTex, SDL_Texture* bottomTex) {
    topPipeTexture = topTex;
    bottomPipeTexture = bottomTex;
    spawnTimer = 0;
    srand(std::time(0));
    pairScored = false;
}

void PipeManager::addPipe()
{
    int minY = -1360;
    int maxY = -980;
    int topY = minY + (rand() % (maxY - minY + 1));

    int bottomY = topY + PIPE_GAP;

    pipes.emplace_back(PIPE_SPAWN_X, topY, true);
    pipes.emplace_back(PIPE_SPAWN_X, bottomY, false);
}
void PipeManager::update()
{

    for (auto& pipe : pipes)
        {
            pipe.move();
        }

    pipes.erase(remove_if(pipes.begin(), pipes.end(),[](const Pipe& pipe) { return pipe.rect.x + PIPE_WIDTH < 0; }),pipes.end());


    spawnTimer++;
    if (spawnTimer >= PIPE_SPAWN_INTERVAL)
        {
            addPipe();
            spawnTimer = 0;
        }
}

void PipeManager::update2()
{

    for (auto& pipe : pipes)
        {
            pipe.move();
        }

    pipes.erase(remove_if(pipes.begin(), pipes.end(),[](const Pipe& pipe) { return pipe.rect.x + PIPE_WIDTH < 0; }),pipes.end());


    spawnTimer++;
    if (spawnTimer >= PIPE_SPAWN_INTERVAL_2)
        {
            addPipe();
            spawnTimer = 0;
        }
}
void PipeManager::update3()
{

    for (auto& pipe : pipes)
        {
            pipe.move();
        }

    pipes.erase(remove_if(pipes.begin(), pipes.end(),[](const Pipe& pipe) { return pipe.rect.x + PIPE_WIDTH < 0; }),pipes.end());


    spawnTimer++;
    if (spawnTimer >= PIPE_SPAWN_INTERVAL_3)
        {
            addPipe();
            spawnTimer = 0;
        }
}
void PipeManager::render(SDL_Renderer* renderer)
{
    for (auto& pipe : pipes)
        {
            SDL_Texture* texture = pipe.isTop ? topPipeTexture : bottomPipeTexture;
            pipe.render(renderer, texture);
        }
}
