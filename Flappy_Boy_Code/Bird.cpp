
#include "Bird.h"
#include <iostream>
 #include <SDL_mixer.h>
using namespace std;
Bird::Bird(vector<SDL_Texture*> textures, float x, float y, int width, int height) :
    mTextures(textures),
    mCurrentFrame(0),
    mAnimationSpeed(12.0f),
    mAnimationTimer(0.0f),
    mX(x),
    mY(y),
    mWidth(width),
    mHeight(height),
    mVelocity(0),
    mGravity(1300.0f),
    mFlapStrength(-400.0f),
    flapSound(NULL)
{
    mRect.x = (int)mX;
    mRect.y = (int)mY;
    mRect.w = mWidth;
    mRect.h = mHeight;
}

Bird::~Bird()
{
}

void Bird::update(float deltaTime, int windowHeight)
{
    mVelocity += mGravity * deltaTime;
    mY = mY + mVelocity * deltaTime;

    if (mY < 0)
        {
            mY = 0;
            mVelocity = 0;
        }
    if (mY > windowHeight - mHeight)
        {
            mY = windowHeight - mHeight;
            mVelocity = 0;
        }

    mRect.x = (int)mX;
    mRect.y = (int)mY;
    mAnimationTimer += deltaTime;

    if (mAnimationTimer >= 1.0f / mAnimationSpeed)
        {
            mCurrentFrame = (mCurrentFrame + 1) % mTextures.size(); // Chuyển sang frame tiếp theo
            mAnimationTimer = 0.0f;
        }

}

void Bird::flap()
{
        mVelocity = mFlapStrength;
     if(flapSound!=NULL)  Mix_PlayChannel(-1, flapSound, 0);

}

void Bird::render(SDL_Renderer* renderer)
{
    SDL_Rect birdRect;
    birdRect.x = (int)mX;
    birdRect.y = (int)mY;
    birdRect.w = mWidth;
    birdRect.h = mHeight;
    SDL_RenderCopy(renderer, mTextures[mCurrentFrame], NULL, &birdRect);
}

SDL_Rect Bird::getRect() const
{
    SDL_Rect rect;
    rect.x = (int)mX;
    rect.y = (int)mY;
    rect.w = mWidth;
    rect.h = mHeight;
    return rect;
}
void Bird::setFlapSound( Mix_Chunk* _flapSound)
{
    this->flapSound= _flapSound;
}
