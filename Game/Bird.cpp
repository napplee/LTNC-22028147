#include "Bird.h"
#include "Game.h"
#include <bits/stdc++.h>
using namespace std;
void Bird::init()
{
    currentRenderingTexture = mid;
    animationFrames = 0;
    score = 0;

    velocity = 0.0f;
    acceleration = 0.0f;

    pos.x = WIDTH / 3 - 32;
    pos.y = HEIGHT / 2;
    pos.w = BIRD_WIDTH;
    pos.h = BIRD_HEIGHT;
}

Bird::Bird(SDL_Texture *up, SDL_Texture *mid, SDL_Texture *down, SDL_Renderer *renderer) : up(up), mid(mid), down(down), renderer(renderer)
{
    init();
}

void Bird::update(bool jump, float elapsedTime)
{
    if(updateFlag != 2){
        elapsedTime = 0;
        updateFlag++;
        updateFlag %= 3;
    }
    elapsedTime *= 5;
    if(jump)
    {
        acceleration = 0.0f;
        velocity = -GRAVITY;
    }
    else
    {
        acceleration += GRAVITY * elapsedTime;
    }

    if(acceleration >= GRAVITY)
        acceleration = GRAVITY;

    velocity += acceleration * elapsedTime;
    pos.y += velocity * elapsedTime;
}

bool Bird::collisionDetector(Pipe *pipe)
{
    // pipe
    if(pipe->top_dst.x <= pos.x + pos.w && pipe->top_dst.x + PIPE_WIDTH >= pos.x + pos.w)
        if(pos.y < pipe->top_dst.y + pipe->top_dst.h || pos.y + pos.h > pipe->bottom_dst.y)
            return true;

    // ground
    if(pos.y + pos.h > HEIGHT - GROUND_HEIGHT)
        return true;

    // ceiling
    if(pos.y < 0)
        return true;

    if(!pipe->passed && pipe->top_dst.x + PIPE_WIDTH < pos.x)
    {
        solveEvent1();
        randomEvent();
        pipe->passed = true;
        score++;
        isIncreaseNumHeart = false;
        if(score > 0 && score % 10 == 0){
            Mix_PlayChannel(-1,newHeart,0);
        }
        if(pipe->passed == true) Mix_PlayChannel(-1,scoreSound,0);
    }

    return false;
}

void Bird::render()
{
    animation();

    if(velocity == 0)
        SDL_RenderCopy(renderer, mid, NULL, &pos);
    else if(velocity < 50)
        SDL_RenderCopyEx(renderer, currentRenderingTexture, NULL, &pos, -30.0, NULL, SDL_FLIP_NONE);
    else if(velocity >= 50 && velocity < 200)
        SDL_RenderCopyEx(renderer, currentRenderingTexture, NULL, &pos, 30.0, NULL, SDL_FLIP_NONE);
    else if(velocity >= 200)
        SDL_RenderCopyEx(renderer, mid, NULL, &pos, 90.0, NULL, SDL_FLIP_NONE);

}

void Bird::animation()
{
    animationFrames++;

    if(animationFrames == 5)
        currentRenderingTexture = down;
    else if(animationFrames == 15)
        currentRenderingTexture = mid;
    else if(animationFrames == 20)
    {
        animationFrames = 0;
        currentRenderingTexture = up;
    }
}
void Bird::revive(int coor){
        pos.y = coor;
}
void Bird::updateVelocity(float vel){
     velocity = vel;
}
bool Bird::checkIsPassedForEvent(Pipe *pipe){
    if(!pipe->passed && pipe->top_dst.x + PIPE_WIDTH < pos.x) return true;
    return false;
}
void Bird::randomEvent(){
    if(score >= currentEventPoint + 2){
        int percent = randomInRangeBird(1,100);
        //cout << percent << endl;
        if(percent <= 25){
            typeEvent = 1;
            currentEventPoint = score;
            randomE = randomInRangeBird(1,2);
        }
        // event 2
        if(percent <= 100 && percent >= 70){
            typeEvent = 2;
            currentEventPoint = score;
            randomE = randomInRangeBird(1,3);
            SDL_Texture *upB;
            SDL_Texture *downB;
            SDL_Texture *midB;
            if(randomE == 1){
                midB = IMG_LoadTexture(renderer, "sprites/bird_orange_0.png");
                upB = IMG_LoadTexture(renderer, "sprites/bird_orange_1.png");
                downB = IMG_LoadTexture(renderer, "sprites/bird_orange_2.png");
            }
            if(randomE == 2){
                midB = IMG_LoadTexture(renderer, "sprites/bird_blue_0.png");
                upB = IMG_LoadTexture(renderer, "sprites/bird_blue_1.png");
                downB = IMG_LoadTexture(renderer, "sprites/bird_blue_2.png");
            }
            if(randomE == 3){
                midB = IMG_LoadTexture(renderer, "sprites/bird_red_0.png");
                upB = IMG_LoadTexture(renderer, "sprites/bird_red_1.png");
                downB = IMG_LoadTexture(renderer, "sprites/bird_red_2.png");
            }
            randomE = 0;
            up = upB;
            mid = midB;
            down = downB;
        }
        if(percent <= 69 && percent >= 40){
            typeEvent = 3;
            backgroundFlag = 1 - backgroundFlag;
            typeEvent = 0;
        }
        if(percent < 40 && percent >= 35){
            typeEvent = 4;
        }
    }
}
int Bird::randomInRangeBird(int x,int y){

    return x + (rand() % (y-x));
}
void Bird::solveEvent1(){
    if(score > currentEventPoint + 1){
        if(typeEvent == 1) updateVelocity(oldVel);
        randomE = 0;
    }
}
