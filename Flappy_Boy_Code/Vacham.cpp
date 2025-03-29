
#include "Vacham.h"
#include "Score.h"
#include <iostream>
 bool Vacham::CheckVaCham(const Bird& bird, PipeManager& pipeManager, Score& score)
 {
    SDL_Rect birdRect = bird.getRect();
    bool hasCollision = false;
    bool hasScored = false;
    for (auto& pipe : pipeManager.pipes)
        {
            SDL_Rect pipeRect;
            pipeRect.x = (int)pipe.rect.x;
            pipeRect.y = (int)pipe.rect.y;
            pipeRect.w = (int)pipe.rect.w;
            pipeRect.h = (int)pipe.rect.h;
                if (SDL_HasIntersection(&birdRect, &pipeRect))
                    {
                        hasCollision = true;
                    }
                else if (bird.getX() > pipeRect.x + PIPE_WIDTH && !pipe.scored && !hasCollision)
                    {
                        score.increaseScore(1);
                        pipe.scored = true;

                    }
        }
    return hasCollision;
}
