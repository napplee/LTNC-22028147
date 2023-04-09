#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <list>
#include <chrono>
#include <random>
#include <time.h>
#include <string>

#include "Bird.h"
#include "Pipe.h"
#include "defs.h"

class Game
{
    public:
        Bird *bird;
        bool isStartingTheme = true;
        bool isStartingThemeFlag = false;
        bool tempFlag = false;
        bool isPause = true;
        int coorRevive = 0;
        int numHeart = 2;
        int flag = 0;
        int numberPlayMusic = 0;
        bool firstTime = true;
        int tmpMusic = 0;

        Mix_Chunk* music = Mix_LoadWAV("fly.wav");
        Mix_Chunk* deadSound = Mix_LoadWAV("crash.wav");
        Mix_Music* backgroundSound = Mix_LoadMUS("ungquachung.mp3");
        int score;
        TTF_Font* font = TTF_OpenFont("font.ttf", 30);
        SDL_Color White = {255, 255, 255};
        int high_score = 0;
        SDL_Texture *tex_background;
        SDL_Texture *tex_ground;
        SDL_Texture *tex_playerUp;
        SDL_Texture *tex_playerMid;
        SDL_Texture *tex_playerDown;
        SDL_Texture *tex_pipe;
        SDL_Texture *tex_numbers[10];
        SDL_Texture *tex_gameover;

        bool isRunning;

        Game(const char *title, int _width, int _height);

        void Start();
        void Close();
        void update(bool jump, float elapsedTime, bool &gameover);
        void render();
        void gameOver();
        void init();
        void renderHighScoreAndHeart();
        void gamePause();
        void gameResume();
        int randomInRange(int x,int y);
        void renderStartingTheme(bool ok);

    private:
        SDL_Renderer *renderer;
        SDL_Window *window;

        SDL_Event event;



        std::list<Pipe*> pipes;

        int ground1, ground2;

        bool gameStarted, gameover;

        void loadTextures();
};



#endif // GAME_H_INCLUDED
