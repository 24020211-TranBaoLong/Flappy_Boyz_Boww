#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include "Window.h"
#include "Bird.h"
#include "Object.h"
#include "Vacham.h"
#include "Score.h"
#include "Board.h"
#include "High.h"
using namespace std;

enum GameState
{
MENU,
PLAYING,
GAME_OVER,
INSTRUCTIONS
};
int main(int argc, char* argv[])
{
if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
cout << "Init Error" << SDL_GetError() << endl;
return 1;
}
if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
cout << "IMG_Init Error" << SDL_GetError();
return 1;
}
if (TTF_Init() == -1) {
std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
return 1;
}
if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
cout << "Mix_Init Error: " << Mix_GetError() << endl;
SDL_Quit();
return 1;
}
if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
cout << "Mix_OpenAudio Error: " << Mix_GetError() << endl;
Mix_Quit();
SDL_Quit();
return 1;
}
int windowWidth = 576 * 2;
int windowHeight = 324 * 2;
rendererWindow window("FLAPPY BOYZ", windowWidth, windowHeight);

// Load background -------------------------------------------------------------------------------------------------------------------------------
SDL_Texture* bg1Layer1 = window.loadTexture("Background/Nen.png");
SDL_Texture* bg1Layer2 = window.loadTexture("Background/mayxa.png");
SDL_Texture* bg1Layer3 = window.loadTexture("Background/moutain.png");
SDL_Texture* bg1Layer4 = window.loadTexture("Background/may1.png");
SDL_Texture* bg1Layer5 = window.loadTexture("Background/may2.png");

SDL_Texture* bg2Layer1 = window.loadTexture("Background/Back21.png");
SDL_Texture* bg2Layer2 = window.loadTexture("Background/Back22.png");
SDL_Texture* bg2Layer3 = window.loadTexture("Background/Back23.png");
SDL_Texture* bg2Layer4 = window.loadTexture("Background/Back24.png");
SDL_Texture* bg2Layer5 = window.loadTexture("Background/Back25.png");

SDL_Texture* bg3Layer1 = window.loadTexture("Background/Back31.png");
SDL_Texture* bg3Layer2 = window.loadTexture("Background/Back32.png");
SDL_Texture* bg3Layer3 = window.loadTexture("Background/Back33.png");
SDL_Texture* bg3Layer4 = window.loadTexture("Background/Back34.png");
SDL_Texture* bg3Layer5 = window.loadTexture("Background/Back35.png");

if (!bg1Layer1 || !bg1Layer2 || !bg1Layer3 || !bg1Layer4 || !bg1Layer5 ||
    !bg2Layer1 || !bg2Layer2 || !bg2Layer3 || !bg2Layer4 || !bg2Layer5 ||
    !bg3Layer1 || !bg3Layer2 || !bg3Layer3 || !bg3Layer4 || !bg3Layer5) {
    cout << "Không thể load ảnh nền" << endl;
    window.cleanup();
    SDL_Quit();
    return 1;
}

int bgWidth = 576;
int bgHeight = 324;
int scaledWidth = bgWidth * 2;
int scaledHeight = bgHeight * 2;

float scrollSpeed1 = 10.0f;
float scrollSpeed2 = 20.0f;
float scrollSpeed3 = 10.0f;
float scrollSpeed4 = 60.0f;
float scrollSpeed5 = 120.0f;

float scrollX1 = 0.0f;
float scrollX2 = 0.0f;
float scrollX3 = 0.0f;
float scrollX4 = 0.0f;
float scrollX5 = 0.0f;

Uint32 lastTime = SDL_GetTicks();

// Load anh chim va cua cac cap pipe-------------------------------------------------------------------------------------------------------
vector<SDL_Texture*> birdTextures;
birdTextures.push_back(window.loadTexture("Bird_Pipe/frame-1.png"));
birdTextures.push_back(window.loadTexture("Bird_Pipe/frame-2.png"));

if (birdTextures.size() != 2) {
    cout << "Không thể load đủ ảnh chim" << endl;
    window.cleanup();
    SDL_Quit();
    return 1;
}

int birdWidth = 30 * 2;
int birdHeight = 30 * 2;
float birdX = 250;
float birdY = windowHeight / 2;
Bird bird(birdTextures, birdX, birdY, birdWidth, birdHeight);


SDL_Texture* topPipeTexture = window.loadTexture("Bird_Pipe/pipetren.png");
SDL_Texture* bottomPipeTexture = window.loadTexture("Bird_Pipe/pipeduoi.png");

if (!topPipeTexture || !bottomPipeTexture) {
    cout << "Không thể load ảnh ống nước" << endl;
    return 1;
}

PipeManager pipeManager(topPipeTexture, bottomPipeTexture);
  Vacham vacham;
//Load anh text-------------------------------------------------------------------------------------------------------------------------
SDL_Color scoreColor = { 0, 51, 51 };
Score score(window.gRender, "Text/arial.ttf", 35, scoreColor);

SDL_Color board1Color = { 255, 100, 0 };
SDL_Color board2Color = { 0, 0, 51 };
SDL_Color board3Color = { 0, 0, 51 };
SDL_Color board4Color = { 0, 0, 51 };
Board board1(window.gRender, "Text/game.ttf", 135, board1Color);
Board board2(window.gRender, "Text/text.ttf", 30, board2Color);
Board board3(window.gRender, "Text/text.ttf", 30, board3Color);
Board board4(window.gRender, "Text/text.ttf", 30, board4Color);
Board high(window.gRender, "Text/arial.ttf", 35, scoreColor);

// Load am thanh------------------------------------------------------------------------------------------------------------------------
Mix_Music* backgroundMusic = Mix_LoadMUS("Sound/background.mp3");
Mix_Chunk* flapSound = Mix_LoadWAV("Sound/flap.wav");

if (!backgroundMusic || !flapSound) {
    cout << "Không thể load nhạc nền hoặc âm thanh" << endl;
}

Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
Mix_VolumeChunk(flapSound, MIX_MAX_VOLUME / 2);
bird.setFlapSound(flapSound);
//-----------------------------------------------------------------------------------------------------------------------------------------------
int finalScore = 0;
bool GameRunning = true;
bool gameOver = false;

SDL_Texture* BangSelect = window.loadTexture("background/bangselect.png");
SDL_Texture* Banghuongdan = window.loadTexture("background/Bangguide.png");
SDL_Rect Rectstart;
SDL_Rect Rect_BangSelect;
SDL_Rect Rect_Bangguide;
Rectstart.x = 0;
Rectstart.y = 0;
Rectstart.w = scaledWidth;
Rectstart.h = scaledHeight;

Rect_BangSelect.x = 355;
Rect_BangSelect.y = 100;
Rect_BangSelect.w = 433;
Rect_BangSelect.h = 577;

Rect_Bangguide.x = 255;
Rect_Bangguide.y = 20;
Rect_Bangguide.w = 433*1.5;
Rect_Bangguide.h = 577*1.5;


GameState currentState = MENU;
int selectedMap = 0;
HighscoreManager highscoreManager("Highscore.txt");

//Chay game_-----------------------------------------------------------------------------------------------------------------------------------
while (GameRunning)
    {
    SDL_Event event;
    int highscore1 = highscoreManager.getHighscore();

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            GameRunning = false;
        }

    //Chia cau truc game:--------------------------------------------------------
        switch (currentState) {
            case MENU:
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_1) {
                        selectedMap = 1;
                        currentState = PLAYING;
                        Mix_PlayMusic(backgroundMusic, -1);
                    } else if (event.key.keysym.sym == SDLK_2) {
                        selectedMap = 2;
                        currentState = PLAYING;
                        Mix_PlayMusic(backgroundMusic, -1);
                    }
                    else if (event.key.keysym.sym == SDLK_3) {
                        selectedMap = 3;
                        currentState = PLAYING;
                         Mix_PlayMusic(backgroundMusic, -1);
                    }
                    else if (event.key.keysym.sym == SDLK_4) {
                         currentState = INSTRUCTIONS;
                    }
                }
                break;

            case PLAYING:
                if (event.type == SDL_KEYDOWN) {
                    if (gameOver) {
                        if (event.key.keysym.sym == SDLK_r)
                            {

                            score.reset();
                            bird = Bird(birdTextures, birdX, birdY, birdWidth, birdHeight);
                            pipeManager = PipeManager(topPipeTexture, bottomPipeTexture);
                            gameOver = false;
                            board1.clearMessages();
                            board2.clearMessages();
                            board3.clearMessages();
                            board4.clearMessages();
                            Mix_PlayMusic(backgroundMusic, -1);
                            }
                        else if (event.key.keysym.sym == SDLK_ESCAPE)
                            {
                            GameRunning = false;
                        }
                        else if (event.key.keysym.sym == SDLK_e)
                            {
                            currentState = MENU;
                            selectedMap = 0;
                            gameOver = false;
                            Mix_HaltMusic();
                        }
                    } else {
                        Mix_PlayChannel(-1, flapSound, 0);
                        bird.flap();
                    }
                }
                break;

            case GAME_OVER:
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_r) {

                        score.reset();
                        bird = Bird(birdTextures, birdX, birdY, birdWidth, birdHeight);
                        pipeManager = PipeManager(topPipeTexture, bottomPipeTexture);
                        gameOver = false;
                        board1.clearMessages();
                        board2.clearMessages();
                        board3.clearMessages();
                        Mix_PlayMusic(backgroundMusic, -1);
                        currentState = PLAYING;
                    } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                        GameRunning = false;
                    } else if (event.key.keysym.sym == SDLK_e) {
                        currentState = MENU;
                        selectedMap = 0;
                        gameOver = false;
                        Mix_HaltMusic();
                    }
                    else if (event.key.keysym.sym == SDLK_4) {
                         currentState = INSTRUCTIONS;
                    }
                }
                break;
                 case INSTRUCTIONS:
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_e) {
                        currentState = MENU; //
                    }
                }
                break;
        }
    }

        high.addMessage("HIGHSCORE: "+to_string(highscore1),10,60);

    switch (currentState) {
        case MENU:

            window.clear();
            window.copy(bg1Layer1, Rectstart);
            window.copy(bg1Layer2, Rectstart);
            window.copy(bg1Layer3, Rectstart);
            window.copy(bg1Layer4, Rectstart);
            window.copy(bg1Layer5, Rectstart);
            window.copy(BangSelect, Rect_BangSelect);

            window.present();
            SDL_Delay(1);
            break;

        case PLAYING: {

            Uint32 currentTime = SDL_GetTicks();
            float deltaTime = (currentTime - lastTime) / 1000.0f;
            lastTime = currentTime;



            if (!gameOver&&selectedMap==1)
                {
                    bird.update(deltaTime, windowHeight);
                    pipeManager.update();
                }
            else  if (!gameOver&&selectedMap==2)
                {
                    bird.update(deltaTime, windowHeight);
                    pipeManager.update2();
                }
                else  if (!gameOver&&selectedMap==3)
                {
                    bird.update(deltaTime, windowHeight);
                    pipeManager.update3();
                }

            window.clear();

 //Ve cac lop map------------------------------------------------------------------------------------------------------------------------------
            SDL_Rect bgRect1a, bgRect1b, bgRect2a, bgRect2b, bgRect3a, bgRect3b, bgRect4a, bgRect4b, bgRect5a, bgRect5b;
            bgRect1a.x = (int)scrollX1;
            bgRect1a.y = 0;
            bgRect1a.w = scaledWidth;
            bgRect1a.h = scaledHeight;

            bgRect1b.x = (int)scrollX1 + scaledWidth;
            bgRect1b.y = 0;
            bgRect1b.w = scaledWidth;
            bgRect1b.h = scaledHeight;

            bgRect2a.x = (int)scrollX2;
            bgRect2a.y = 0;
            bgRect2a.w = scaledWidth;
            bgRect2a.h = scaledHeight;

            bgRect2b.x = (int)scrollX2 + scaledWidth;
            bgRect2b.y = 0;
            bgRect2b.w = scaledWidth;
            bgRect2b.h = scaledHeight;

            bgRect3a.x = (int)scrollX3;
            bgRect3a.y = 0;
            bgRect3a.w = scaledWidth;
            bgRect3a.h = scaledHeight;

            bgRect3b.x = (int)scrollX3 + scaledWidth;
            bgRect3b.y = 0;
            bgRect3b.w = scaledWidth;
            bgRect3b.h = scaledHeight;

            bgRect4a.x = (int)scrollX4;
            bgRect4a.y = 0;
            bgRect4a.w = scaledWidth;
            bgRect4a.h = scaledHeight;

            bgRect4b.x = (int)scrollX4 + scaledWidth;
            bgRect4b.y = 0;
            bgRect4b.w = scaledWidth;
            bgRect4b.h = scaledHeight;

            bgRect5a.x = (int)scrollX5;
            bgRect5a.y = 0;
            bgRect5a.w = scaledWidth;
            bgRect5a.h = scaledHeight;

            bgRect5b.x = (int)scrollX5 + scaledWidth;
            bgRect5b.y = 0;
            bgRect5b.w = scaledWidth;
            bgRect5b.h = scaledHeight;
            switch (selectedMap) {
                case 1:
                     scrollX1 -= scrollSpeed1 * deltaTime;
                    if (scrollX1 < -scaledWidth) {
                        scrollX1 = 0;
                        }

                        scrollX2 -= scrollSpeed2 * deltaTime;
                        if (scrollX2 < -scaledWidth) {
                            scrollX2 = 0;
                        }

                        scrollX3 -= scrollSpeed3 * deltaTime;
                        if (scrollX3 < -scaledWidth) {
                            scrollX3 = 0;
                        }

                        scrollX4 -= scrollSpeed4 * deltaTime;
                        if (scrollX4 < -scaledWidth) {
                            scrollX4 = 0;
                        }

                        scrollX5 -= scrollSpeed5 * deltaTime;
                        if (scrollX5 < -scaledWidth) {
                            scrollX5 = 0;
                        }
                    window.copy(bg1Layer1, bgRect1a);
                    window.copy(bg1Layer1, bgRect1b);
                    window.copy(bg1Layer2, bgRect2a);
                    window.copy(bg1Layer2, bgRect2b);
                    window.copy(bg1Layer3, bgRect3a);
                    window.copy(bg1Layer3, bgRect3b);
                    window.copy(bg1Layer4, bgRect4a);
                    window.copy(bg1Layer4, bgRect4b);
                    window.copy(bg1Layer5, bgRect5a);
                    window.copy(bg1Layer5, bgRect5b);
                    break;
                case 2:
                 scrollX1 -= scrollSpeed1 * deltaTime;
                    if (scrollX1 < -scaledWidth) {
                        scrollX1 = 0;
                        }

                        scrollX2 -= scrollSpeed2 * deltaTime;
                        if (scrollX2 < -scaledWidth) {
                            scrollX2 = 0;
                        }

                        scrollX3 -= scrollSpeed3 * deltaTime;
                        if (scrollX3 < -scaledWidth) {
                            scrollX3 = 0;
                        }

                        scrollX4 -= scrollSpeed4 * deltaTime;
                        if (scrollX4 < -scaledWidth) {
                            scrollX4 = 0;
                        }

                        scrollX5 -= scrollSpeed5 * deltaTime;
                        if (scrollX5 < -scaledWidth) {
                            scrollX5 = 0;
                        }
                    window.copy(bg2Layer1, bgRect1a);
                    window.copy(bg2Layer1, bgRect1b);
                    window.copy(bg2Layer2, bgRect2a);
                    window.copy(bg2Layer2, bgRect2b);
                    window.copy(bg2Layer3, bgRect3a);
                    window.copy(bg2Layer3, bgRect3b);
                    window.copy(bg2Layer4, bgRect4a);
                    window.copy(bg2Layer4, bgRect4b);
                    window.copy(bg2Layer5, bgRect5a);
                    window.copy(bg2Layer5, bgRect5b);
                    break;
                case 3:
                    scrollX1 -= scrollSpeed1 * deltaTime;
                    if (scrollX1 < -scaledWidth) {
                        scrollX1 = 0;
                        }

                        scrollX2 -= scrollSpeed2 * deltaTime;
                        if (scrollX2 < -scaledWidth) {
                            scrollX2 = 0;
                        }

                        scrollX3 -= scrollSpeed3 * deltaTime;
                        if (scrollX3 < -scaledWidth) {
                            scrollX3 = 0;
                        }

                        scrollX4 -= scrollSpeed4 * deltaTime;
                        if (scrollX4 < -scaledWidth) {
                            scrollX4 = 0;
                        }

                        scrollX5 -= scrollSpeed5 * deltaTime;
                        if (scrollX5 < -scaledWidth) {
                            scrollX5 = 0;
                        }
                    window.copy(bg3Layer1, bgRect1a);
                    window.copy(bg3Layer1, bgRect1b);
                    window.copy(bg3Layer2, bgRect2a);
                    window.copy(bg3Layer2, bgRect2b);
                    window.copy(bg3Layer3, bgRect3a);
                    window.copy(bg3Layer3, bgRect3b);
                    window.copy(bg3Layer4, bgRect4a);
                    window.copy(bg3Layer4, bgRect4b);
                    window.copy(bg3Layer5, bgRect5a);
                    window.copy(bg3Layer5, bgRect5b);
                    break;
                default:
                    break;
            }
            pipeManager.render(window.gRender);
            bird.render(window.gRender);
            score.render(window.gRender, 10, 10);
            high.render(window.gRender);

            if (!gameOver && vacham.CheckVaCham(bird, pipeManager, score))
            {
                gameOver = true;
                currentState = GAME_OVER;
                finalScore = score.getScore();
                highscoreManager.saveHighscore(finalScore);
                board1.clearMessages();
                board2.clearMessages();
                board3.clearMessages();
                board4.clearMessages();
                high.clearMessages();
                board1.addMessage(" FLAPPY BOYZ!", 250, 220);
                board2.addMessage("Press 'R' to PLAY or 'ESC' to EXIT", 213, 400);
                board3.addMessage("Press 'E' to back to MENU",213,450);
                board4.addMessage("Your Score:"+to_string(finalScore), 213, 350);
                Mix_HaltMusic();
            }

            window.present();

            SDL_Delay(1);
            break;
        }

        case GAME_OVER:
        {

            Uint32 currentTime = SDL_GetTicks();
            float deltaTime = (currentTime - lastTime) / 1000.0f;
            lastTime = currentTime;

            window.clear();
//Ve khi thua:-----------------------------------------------------------------------------------------------------------------------------
            SDL_Rect bgRect1a, bgRect1b, bgRect2a, bgRect2b, bgRect3a, bgRect3b, bgRect4a, bgRect4b, bgRect5a, bgRect5b;
            bgRect1a.x = (int)scrollX1;
            bgRect1a.y = 0;
            bgRect1a.w = scaledWidth;
            bgRect1a.h = scaledHeight;

            bgRect1b.x = (int)scrollX1 + scaledWidth;
            bgRect1b.y = 0;
            bgRect1b.w = scaledWidth;
            bgRect1b.h = scaledHeight;

            bgRect2a.x = (int)scrollX2;
            bgRect2a.y = 0;
            bgRect2a.w = scaledWidth;
            bgRect2a.h = scaledHeight;

            bgRect2b.x = (int)scrollX2 + scaledWidth;
            bgRect2b.y = 0;
            bgRect2b.w = scaledWidth;
            bgRect2b.h = scaledHeight;

            bgRect3a.x = (int)scrollX3;
            bgRect3a.y = 0;
            bgRect3a.w = scaledWidth;
            bgRect3a.h = scaledHeight;

            bgRect3b.x = (int)scrollX3 + scaledWidth;
            bgRect3b.y = 0;
            bgRect3b.w = scaledWidth;
            bgRect3b.h = scaledHeight;

            bgRect4a.x = (int)scrollX4;
            bgRect4a.y = 0;
            bgRect4a.w = scaledWidth;
            bgRect4a.h = scaledHeight;

            bgRect4b.x = (int)scrollX4 + scaledWidth;
            bgRect4b.y = 0;
            bgRect4b.w = scaledWidth;
            bgRect4b.h = scaledHeight;

            bgRect5a.x = (int)scrollX5;
            bgRect5a.y = 0;
            bgRect5a.w = scaledWidth;
            bgRect5a.h = scaledHeight;

            bgRect5b.x = (int)scrollX5 + scaledWidth;
            bgRect5b.y = 0;
            bgRect5b.w = scaledWidth;
            bgRect5b.h = scaledHeight;
            switch (selectedMap) {
            case 1:
                scrollX1 -= scrollSpeed1 * deltaTime;
                if (scrollX1 < -scaledWidth) {
                    scrollX1 = 0;
                }

                scrollX2 -= scrollSpeed2 * deltaTime;
                if (scrollX2 < -scaledWidth) {
                    scrollX2 = 0;
                }

                scrollX3 -= scrollSpeed3 * deltaTime;
                if (scrollX3 < -scaledWidth) {
                    scrollX3 = 0;
                }

                scrollX4 -= scrollSpeed4 * deltaTime;
                if (scrollX4 < -scaledWidth) {
                    scrollX4 = 0;
                }

                scrollX5 -= scrollSpeed5 * deltaTime;
                if (scrollX5 < -scaledWidth) {
                    scrollX5 = 0;
                }
                window.copy(bg1Layer1, bgRect1a);
                window.copy(bg1Layer1, bgRect1b);
                window.copy(bg1Layer2, bgRect2a);
                window.copy(bg1Layer2, bgRect2b);
                window.copy(bg1Layer3, bgRect3a);
                window.copy(bg1Layer3, bgRect3b);
                window.copy(bg1Layer4, bgRect4a);
                window.copy(bg1Layer4, bgRect4b);
                window.copy(bg1Layer5, bgRect5a);
                window.copy(bg1Layer5, bgRect5b);
                break;
            case 2:
                scrollX1 -= scrollSpeed1 * deltaTime;
                if (scrollX1 < -scaledWidth) {
                    scrollX1 = 0;
                }

                scrollX2 -= scrollSpeed2 * deltaTime;
                if (scrollX2 < -scaledWidth) {
                    scrollX2 = 0;
                }

                scrollX3 -= scrollSpeed3 * deltaTime;
                if (scrollX3 < -scaledWidth) {
                    scrollX3 = 0;
                }

                scrollX4 -= scrollSpeed4 * deltaTime;
                if (scrollX4 < -scaledWidth) {
                    scrollX4 = 0;
                }

                scrollX5 -= scrollSpeed5 * deltaTime;
                if (scrollX5 < -scaledWidth) {
                    scrollX5 = 0;
                }
                window.copy(bg2Layer1, bgRect1a);
                window.copy(bg2Layer1, bgRect1b);
                window.copy(bg2Layer2, bgRect2a);
                window.copy(bg2Layer2, bgRect2b);
                window.copy(bg2Layer3, bgRect3a);
                window.copy(bg2Layer3, bgRect3b);
                window.copy(bg2Layer4, bgRect4a);
                window.copy(bg2Layer4, bgRect4b);
                window.copy(bg2Layer5, bgRect5a);
                window.copy(bg2Layer5, bgRect5b);
                break;
            case 3:
                scrollX1 -= scrollSpeed1 * deltaTime;
                if (scrollX1 < -scaledWidth) {
                    scrollX1 = 0;
                }

                scrollX2 -= scrollSpeed2 * deltaTime;
                if (scrollX2 < -scaledWidth) {
                    scrollX2 = 0;
                }

                scrollX3 -= scrollSpeed3 * deltaTime;
                if (scrollX3 < -scaledWidth) {
                    scrollX3 = 0;
                }

                scrollX4 -= scrollSpeed4 * deltaTime;
                if (scrollX4 < -scaledWidth) {
                    scrollX4 = 0;
                }

                scrollX5 -= scrollSpeed5 * deltaTime;
                if (scrollX5 < -scaledWidth) {
                    scrollX5 = 0;
                }
                window.copy(bg3Layer1, bgRect1a);
                window.copy(bg3Layer1, bgRect1b);
                window.copy(bg3Layer2, bgRect2a);
                window.copy(bg3Layer2, bgRect2b);
                window.copy(bg3Layer3, bgRect3a);
                window.copy(bg3Layer3, bgRect3b);
                window.copy(bg3Layer4, bgRect4a);
                window.copy(bg3Layer4, bgRect4b);
                window.copy(bg3Layer5, bgRect5a);
                window.copy(bg3Layer5, bgRect5b);
                break;

            default:

                break;
            }

            board1.render(window.gRender);
            board2.render(window.gRender);
            board3.render(window.gRender);
            board4.render(window.gRender);
            window.present();
            SDL_Delay(1);
            break;
        }

            case INSTRUCTIONS:
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_e)
                        {
                        currentState = MENU;
                    }
                }
                window.clear();
                window.copy(bg1Layer1, Rectstart);
                window.copy(bg1Layer2, Rectstart);
                window.copy(bg1Layer3, Rectstart);
                window.copy(bg1Layer4, Rectstart);
                window.copy(bg1Layer5, Rectstart);
                window.copy(Banghuongdan, Rect_Bangguide);
                window.present();
                SDL_Delay(1);
                break;
    }
}

// Clean up
window.cleanup();
TTF_Quit();
Mix_FreeMusic(backgroundMusic);
Mix_FreeChunk(flapSound);
Mix_Quit();
SDL_Quit();

return 0;
}
