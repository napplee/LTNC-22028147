#ifndef BIRD_H_INCLUDED
#define BIRD_H_INCLUDED

#include <SDL.h>
#include <iostream>
#include <SDL_mixer.h>
#include "Pipe.h"
#include "defs.h"

class Bird
{
    private:
        float velocity;
        float acceleration;

        SDL_Rect pos;

        SDL_Texture *up;
        SDL_Texture *down;
        SDL_Texture *mid;
        SDL_Texture *currentRenderingTexture;
        SDL_Renderer *renderer;

        int animationFrames;


    public:
        int backgroundFlag = 0;
        int typeEvent = 0;
        int randomE = 0;
        int currentEventPoint = 0;
        int oldVel=0;
        int score;
        int updateFlag = 0;
        bool isIncreaseNumHeart = false;
        Mix_Chunk* newHeart = Mix_LoadWAV("xpsound.mp3");
        Mix_Chunk* scoreSound = Mix_LoadWAV("score.wav");
        Bird(SDL_Texture *up, SDL_Texture *mid, SDL_Texture *down, SDL_Renderer *renderer);
        int getScore()
        {
            return score;
        }
        void init();
        void render();
        void update(bool jump, float elapsedTime);
        void animation();
        bool collisionDetector(Pipe *pipe);
        void revive(int coor);
        void updateWhenRevive(int posY);
        int getPosY(Bird bird);
        void updateVelocity(float vel);
        bool checkIsPassedForEvent(Pipe *pipe);
        void randomEvent();
        int randomInRangeBird(int x,int y);
        void solveEvent1();
};

#endif // BIRD_H_INCLUDED
