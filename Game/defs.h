#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#define WIDTH 479
#define HEIGHT 639

#define FPS 60
#define frameDelay 1000 / FPS

#define GRAVITY 80.0f

#define BIRD_WIDTH 55
#define BIRD_HEIGHT 39

#define PIPE_WIDTH 80
#define PIPE_WIDTH_SRC 52
#define PIPE_GAP 170
#define PIPE_DISTANCE 300 // 200 -> 350
#define PIPE_V 3

#define PIPE_MIN_H 150
#define PIPE_MAX_H 450

#define GROUND_HEIGHT 112
#define GROUND_WIDTH 336
#define GAP_MIN 150
#define GAP_MAX 200
const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};


#endif // DEFS_H_INCLUDED
