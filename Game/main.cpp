
#include "defs.h"
#include "Game.cpp"
#undef main

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    Mix_Init(0);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2,1024);

    Game game("Flappy bird", WIDTH, HEIGHT);

    game.Start();

    return 0;
}
