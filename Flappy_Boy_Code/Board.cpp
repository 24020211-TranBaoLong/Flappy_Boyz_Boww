

#include "Board.h"
#include <iostream>
using namespace std;
Board::Board(SDL_Renderer* renderer, const char* fontPath, int fontSize, SDL_Color color) :
    mRenderer(renderer),
    mFont(TTF_OpenFont(fontPath, fontSize)),
    mColor(color)
{
    if (!mFont)
        {
            cout << "TTF_OpenFont Error: " << TTF_GetError() << endl;
        }
}

Board::~Board()
{
    TTF_CloseFont(mFont);
    clearMessages();
}

void Board::addMessage(const string& message, int x, int y)
{
    Message newMessage;
    newMessage.text = message;
    newMessage.x = x;
    newMessage.y = y;
    newMessage.texture = NULL;
    createTextureForMessage(newMessage);
    mMessages.push_back(newMessage);
}

void Board::clearMessages()
{
    for (auto& message : mMessages)
        {
            SDL_DestroyTexture(message.texture);
        }
            mMessages.clear();
}

void Board::render(SDL_Renderer* renderer)
{
    for (auto& message : mMessages)
        {
            if (message.texture)
            {
                SDL_Rect textRect;
                SDL_QueryTexture(message.texture, NULL, NULL, &textRect.w, &textRect.h);
                textRect.x = message.x;
                textRect.y = message.y;
                SDL_RenderCopy(renderer, message.texture, NULL, &textRect);
            }
        }
}

void Board::createTextureForMessage(Message& message)
{

    if (message.texture)
        {
            SDL_DestroyTexture(message.texture);
            message.texture = NULL;
        }

    SDL_Surface* surface = TTF_RenderText_Solid(mFont, message.text.c_str(), mColor);
    if (!surface)
        {
            cout << "TTF_RenderText_Solid Error: " << TTF_GetError() << endl;
            return;
        }


    message.texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    if (!message.texture)
        {
           cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
        }


    SDL_FreeSurface(surface);
}
