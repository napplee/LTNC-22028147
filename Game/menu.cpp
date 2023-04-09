#include <bits/stdc++.h>

#include <SDL.h>
#include <iostream>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "defs.h"
#include "Game.h"
using namespace std;
menu::menu(const char *title, int width, int height){
    while(exit == false){
       loadTexture();
       eventHandle();
       render(flag);
    }

}
void menu::loadTexture(){
    play = IMG_LoadTexture(renderer,"play.png");
    played = IMG_LoadTexture(renderer,"played.png");
    title = IMG_LoadTexture(renderer,"title.png");
    background = IMG_LoadTexture(renderer,"background-day.png");
}
void menu::render(int isClick){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,background,NULL,NULL);
    if(flag == 0) SDL_RenderCopy(renderer,play,NULL, new SDL_Rect{WIDTH/2-50,HEIGHT/2,100,50});
    if(flag == 1) SDL_RenderCopy(renderer,played,NULL, new SDL_Rect{WIDTH/2-50,HEIGHT/2,100,50});
    SDL_RenderCopy(renderer,title,NULL,new SDL_Rect{0, 0, WIDTH, HEIGHT/5});
    SDL_RenderPresent(renderer);
}
void menu::eventHandle(){
    SDL_PollEvent(&event);
    int x = event.motion.x, y = event.motion.y;
    if(event.type == SDL_QUIT) exit = true;
    if(Menu){
        if(event.type == SDL_MOUSEBUTTONDOWN && x >= WIDTH/2-50 && x <= WIDTH/2-50 + 100 && y <= HEIGHT/2 + 50 && y >= HEIGHT/2)
        {
            flag = 1;
            SDL_Delay(100);
        }
        else flag = 0;
    }
}
