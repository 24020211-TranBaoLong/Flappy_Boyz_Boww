
#ifndef BOARD_H
#define BOARD_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
using namespace std;
class Board {
public:
    Board(SDL_Renderer* renderer, const char* fontPath, int fontSize, SDL_Color color);
    ~Board();

    void addMessage(const string& message, int x, int y);
    void clearMessages();
    void render(SDL_Renderer* renderer);

private:
    struct Message
    {
        string text;
        int x, y;
        SDL_Texture* texture;
    };

    SDL_Renderer* mRenderer;
    TTF_Font* mFont;
    SDL_Color mColor;
    vector<Message> mMessages;

    void createTextureForMessage(Message& message);
};

#endif
