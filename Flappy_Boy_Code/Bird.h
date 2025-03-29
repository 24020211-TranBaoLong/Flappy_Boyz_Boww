
#ifndef BIRD_H
#define BIRD_H

#include <SDL.h>
#include <vector>
#include<SDL_mixer.h>
using namespace std;
class Bird
{
public:
    Bird(vector<SDL_Texture*> textures, float x, float y, int width, int height);
    virtual ~Bird();

    virtual void update(float deltaTime, int windowHeight);
    virtual void flap();
    virtual void render(SDL_Renderer* renderer);

    float getX() const { return mX; }
    float getY() const { return mY; }
    int getWidth() const { return mWidth; }
    int getHeight() const { return mHeight; }
    SDL_Rect getRect() const;
    void setFlapSound( Mix_Chunk* _flapSound);

private:
    vector<SDL_Texture*> mTextures;
    int mCurrentFrame;
    float mAnimationSpeed;
    float mAnimationTimer;
    float mX, mY;
    int mWidth, mHeight;
    float mVelocity;
    float mGravity;
    float mFlapStrength;
    SDL_Rect mRect;
    Mix_Chunk* flapSound;

};

 #endif
