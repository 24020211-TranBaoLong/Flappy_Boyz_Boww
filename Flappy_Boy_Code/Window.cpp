
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Window.h"

using namespace std;

rendererWindow::rendererWindow(const char* NAME_SCREEN, int WEIGHT_SCREEN, int HIGH_SCREEN)
{
    gWindow = SDL_CreateWindow(NAME_SCREEN, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WEIGHT_SCREEN, HIGH_SCREEN, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        cout << "Khong the tao cua so" << SDL_GetError() << endl;
    }
    gRender = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRender == NULL) {
        cout << "Khong the tao render" << SDL_GetError() << endl;
    }
}

SDL_Texture* rendererWindow::loadTexture(const char* p) {
    SDL_Texture* NewTexture = NULL;
    NewTexture = IMG_LoadTexture(gRender, p);
    if (NewTexture == NULL) {
        cout << "Loi load anh" << IMG_GetError() << endl;
    }
    return NewTexture;
}

void rendererWindow::cleanup() {
    SDL_DestroyRenderer(gRender);
}

void rendererWindow::clear() {
    SDL_RenderClear(gRender);
}

void rendererWindow::copy(SDL_Texture* NewTexture, SDL_Rect rect) {
    SDL_RenderCopy(gRender, NewTexture, NULL, &rect);
}

void rendererWindow::present() {
    SDL_RenderPresent(gRender);
}

void rendererWindow::drawRect(SDL_Rect rect, SDL_Color color) {
    SDL_SetRenderDrawColor(gRender, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(gRender, &rect);
}

void rendererWindow::fillRect(SDL_Rect rect, SDL_Color color) {
    SDL_SetRenderDrawColor(gRender, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(gRender, &rect);
}
