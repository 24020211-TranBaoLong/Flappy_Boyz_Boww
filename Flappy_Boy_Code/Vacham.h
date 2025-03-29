
#ifndef VACHAM_H
#define VACHAM_H

#include <SDL.h>
#include "Bird.h"
#include "Object.h"
#include "Score.h"
#include<iostream>
#include <SDL_mixer.h>
class Vacham {
public:
    static bool CheckVaCham(const Bird& bird, PipeManager& pipeManager, Score& score);
};

#endif
