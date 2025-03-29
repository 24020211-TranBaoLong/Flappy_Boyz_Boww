
#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

class rendererWindow {
public:
    rendererWindow(const char* NAME_SCREEN, int WEIGHT_SCREEN, int HIGH_SCREEN);
    SDL_Texture* loadTexture(const char* p);
    void cleanup();
    void clear();
    void copy(SDL_Texture* Newtexture, SDL_Rect rect);
    void present();

    void drawRect(SDL_Rect rect, SDL_Color color);
    void fillRect(SDL_Rect rect, SDL_Color color);

    SDL_Renderer* gRender = NULL;

private:
    SDL_Window* gWindow = NULL;
};

#endif
