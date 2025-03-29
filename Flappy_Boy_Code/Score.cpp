
#include "Score.h"
#include <iostream>
#include <string>
using namespace std;
Score::Score(SDL_Renderer* renderer, const char* fontPath, int fontSize, SDL_Color color) :
    mScore(0),
    mScore2(0),
    mFont(TTF_OpenFont(fontPath, fontSize)),
    mColor(color),
    mTexture(NULL)
{
    if (!mFont)
        {
            cout << "TTF_OpenFont Error: " << TTF_GetError() << endl;
        }
}

Score::~Score()
{
    SDL_DestroyTexture(mTexture);
    TTF_CloseFont(mFont);
}

void Score::increaseScore(int amount)
{
    mScore += amount;
    mScore2 = mScore/2;
}

int Score::getScore() const
{
    return mScore2;
}

void Score::render(SDL_Renderer* renderer, int x, int y)
{
    string scoreText = "SCORE: " + to_string(mScore2);

    updateTexture(renderer, scoreText);

        if (mTexture)
            {
                SDL_Rect textRect;
                SDL_QueryTexture(mTexture, NULL, NULL, &textRect.w, &textRect.h);
                textRect.x = x;
                textRect.y = y;
                SDL_RenderCopy(renderer, mTexture, NULL, &textRect);
            }
}

void Score::updateTexture(SDL_Renderer* renderer, const string& scoreText)
{

        if (mTexture)
            {
                SDL_DestroyTexture(mTexture);
            }

    SDL_Surface* surface = TTF_RenderText_Solid(mFont, scoreText.c_str(), mColor);
        if (!surface)
            {
                cout << "TTF_RenderText_Solid Error: " << TTF_GetError() << endl;
                return;
            }


    mTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!mTexture)
        {
            cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
        }


    SDL_FreeSurface(surface);
}

void Score::reset()
{   mScore=0;
    mScore2=0;
}
