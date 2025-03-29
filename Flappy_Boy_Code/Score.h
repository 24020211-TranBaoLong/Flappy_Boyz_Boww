
#ifndef SCORE_H
#define SCORE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
using namespace std;
class Score
{
public:
    Score(SDL_Renderer* renderer, const char* fontPath, int fontSize, SDL_Color color);
    ~Score();

    void increaseScore(int amount);
    int getScore() const;
    void render(SDL_Renderer* renderer, int x, int y);
    void reset();
private:
    int mScore;
    int mScore2;
    TTF_Font* mFont;
    SDL_Color mColor;
    SDL_Texture* mTexture;
    void updateTexture(SDL_Renderer* renderer, const string& scoreText);
};

#endif
