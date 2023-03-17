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
        int score;
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
};

#endif // BIRD_H_INCLUDED
