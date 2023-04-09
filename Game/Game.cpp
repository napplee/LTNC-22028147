#include "Game.h"
#include "Bird.cpp"
#include <bits/stdc++.h>
using namespace std;
Game::Game(const char *title, int width, int height)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    isRunning = true;
    gameover = false;

    ground1 = -WIDTH / 2;
    ground2 = WIDTH   / 2;

    srand(time(NULL));

    Start();
}
int Game::randomInRange(int x,int y){

    return x + (rand() % (y-x));
}
void Game::init()
{

    bird->init();

    for(auto pipe : pipes)
        pipes.pop_front();
    //cout << randomInRange(300,450) << "\n";
    //randomInRange(100,200) Khoang cach
    pipes.push_back(new Pipe(WIDTH * 2 + PIPE_DISTANCE, rand() % 301 + 100, randomInRange(GAP_MIN,GAP_MAX)));
    pipes.push_back(new Pipe(pipes.back()->bottom_dst.x + PIPE_DISTANCE, rand() % 301 + 100, randomInRange(GAP_MIN,GAP_MAX)));
    pipes.push_back(new Pipe(pipes.back()->bottom_dst.x + PIPE_DISTANCE, rand() % 301 + 100, randomInRange(GAP_MIN,GAP_MAX)));

    gameStarted = false;
    gameover = false;
    //
    bird->render();
    render();
}

void Game::renderHighScoreAndHeart(){
    string tmp = "High Score: " + to_string(high_score);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, tmp.c_str() , White);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect;
    Message_rect.x = 0;
    Message_rect.y = 0;
    Message_rect.w = surfaceMessage->w;
    Message_rect.h = surfaceMessage->h;

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    //cout << "D";



    // HEART
    SDL_Rect src;
    src.x = src.y = 0; src.w = 0;src.h=0;
    SDL_Texture* tex_numberHeart = IMG_LoadTexture(renderer,"sprites/heart.png");
    SDL_QueryTexture(tex_numberHeart,NULL,NULL,&src.w,&src.h);
    SDL_Rect numberHeart_rect;
    numberHeart_rect.x = 0;
    numberHeart_rect.y = Message_rect.h+ 15;
    numberHeart_rect.w = src.w;
    numberHeart_rect.h = src.h;

    //  number Heart

    string tmp1 = "x " + to_string(numHeart);
    SDL_Surface* surfaceNumHeart = TTF_RenderText_Solid(font, tmp1.c_str() , White);

    SDL_Texture* numberHeart = SDL_CreateTextureFromSurface(renderer, surfaceNumHeart);

    SDL_Rect heart_rect;
    heart_rect.x = numberHeart_rect.w + 15;
    heart_rect.y = numberHeart_rect.y;
    heart_rect.w = surfaceNumHeart->w;
    heart_rect.h = surfaceNumHeart->h;

    SDL_RenderCopy(renderer, numberHeart, NULL, &heart_rect);
    SDL_DestroyTexture(numberHeart);
    SDL_FreeSurface(surfaceNumHeart);

    //
    SDL_RenderCopy(renderer, tex_numberHeart, &src, &numberHeart_rect);

    SDL_DestroyTexture(tex_numberHeart);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}
void Game::renderStartingTheme(bool ok){
    SDL_Texture* play = IMG_LoadTexture(renderer,"sprites/play.png");
    SDL_Texture* played = IMG_LoadTexture(renderer,"sprites/played.png");
    SDL_Texture* title = IMG_LoadTexture(renderer,"sprites/title.png");
    SDL_Texture* startingBackground = IMG_LoadTexture(renderer,"sprites/background-day.png");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,startingBackground,NULL,NULL);
    if(ok == 0) SDL_RenderCopy(renderer,play,NULL, new SDL_Rect{WIDTH/2-50,HEIGHT/2,100,50});
    if(ok == 1) SDL_RenderCopy(renderer,played,NULL, new SDL_Rect{WIDTH/2-50,HEIGHT/2,100,50});
    SDL_RenderCopy(renderer,title,NULL,new SDL_Rect{0, 0, WIDTH, HEIGHT/5});
    SDL_RenderPresent(renderer);
}
void Game::Start()
{
    if(isStartingThemeFlag == true && tempFlag == false) {
            tempFlag = true;
            SDL_RenderClear(renderer);
            loadTextures();
            bird = new Bird(tex_playerDown, tex_playerMid, tex_playerUp, renderer);
            init();
    }
    auto t1 = chrono::system_clock::now();
    auto t2 = t1;
    // main game loop
    while(isRunning)
    {

        t1 = t2;
        t2 = chrono::system_clock::now();

        chrono::duration<float> dt = t2 - t1;

        bool jump = false;
        while(SDL_PollEvent(&event))
        {
            int x = event.motion.x, y = event.motion.y;
            if(event.type == SDL_QUIT)
                {
                    isRunning = false;
                }
            if(isStartingTheme == false) {

                    render();
            }
            if(isStartingTheme == false)
            if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) || (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)||((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)))
                {
                    Mix_PlayChannel(-1,music,0);
                    jump = gameStarted = true;
                    isPause = false;
                    if(firstTime == false) tmpMusic = false;
                    if(firstTime == true && tmpMusic == 1) firstTime = false;
                }
            if(isStartingTheme == true){
                if(event.type == SDL_MOUSEBUTTONDOWN && x >= WIDTH/2-50 && x <= WIDTH/2-50 + 100 && y <= HEIGHT/2 + 50 && y >= HEIGHT/2)
                {
                    isStartingThemeFlag = true;
                }
                renderStartingTheme(isStartingThemeFlag);
                if(isStartingThemeFlag == true && tempFlag == false) {
                        tempFlag = true;
                        SDL_RenderClear(renderer);
                        isStartingTheme = false;
                        loadTextures();
                        bird = new Bird(tex_playerDown, tex_playerMid, tex_playerUp, renderer);
                        init();

                }
            }
            if(event.key.keysym.sym == SDLK_ESCAPE){
                gamePause();
            }
        }
        //cout << gameStarted << " " << tmpMusic << " " << firstTime << endl;
        if(gameStarted == true && tmpMusic == 0 && firstTime == true) {
                tmpMusic = 1;
                Mix_PlayMusic(backgroundSound,0);
                numberPlayMusic++;
                firstTime = false;
                //cout << numberPlayMusic << "\n";
        }


        if(frameDelay > dt.count())
            SDL_Delay(frameDelay - dt.count());

        if(gameStarted)
        {
            if(isPause == false)update(jump, dt.count(), gameover);
            if(gameover)
                {
                    gameOver();
                }
        }
    }

    Close();
}

void Game::gamePause(){

    isPause = true;
    Mix_PauseMusic();
    while(isPause)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                isPause = false;

            if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) || (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP))
                gameResume();
        }
    }
}
void Game::gameResume(){
    isPause = false;
    bird->updateFlag ++;
    Mix_ResumeMusic();
}
void Game::update(bool jump, float elapsedTime, bool &gameover)
{
    if(flag == 0) bird->update(jump, elapsedTime);
    if(flag == 1){
        flag = 0;
        bird->revive(coorRevive);
        bird->updateVelocity(0);
        render();
    }
    int x = 0,coor = 0;
    for(auto p : pipes)
    {
        p->bottom_dst.x -= PIPE_V;
        p->top_dst.x = p->bottom_dst.x;

        if(p->bottom_dst.x + p->bottom_dst.w < 0)
        {
            pipes.pop_front();
            int dis = randomInRange(150,500);
            pipes.push_back(new Pipe(pipes.back()->bottom_dst.x + dis, rand() % 301 + 100, randomInRange(GAP_MIN,GAP_MAX)));
            cout << dis<<"\n";
        }
        // increase heart
        if(bird->collisionDetector(p) == false && bird->isIncreaseNumHeart == false){
            if(bird->score % 10 == 0 && bird->score > 0) {
                    numHeart++;
                    bird->isIncreaseNumHeart = true;
            }
        }
        if(bird->collisionDetector(p))
        {
            Mix_PlayChannel(-1,deadSound,0);
            Mix_PauseMusic();
            if(gameover == false)
            {
                //cout << p->bottom_dst.y << "\n";
                numHeart--;
                if(numHeart > 0) {
                        isPause = true;
                        x = 1;
                        coorRevive = p->top_dst.y + p->top_dst.h + 50;
                        bird->revive(coorRevive);
                        render();
                        while(isPause)
                        {

                            while(SDL_PollEvent(&event))
                            {
                                if(event.type == SDL_QUIT)
                                    isPause = false;

                                if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) || (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) || ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)))
                                    {
                                        isPause = false;
                                        Mix_ResumeMusic();
                                    }
                            }
                        }
                }

                if(numHeart <= 0) gameover = true;

            }
        }

    }

    ground1 -= PIPE_V;
    ground2 -= PIPE_V;

    if(ground1 + WIDTH < 0)
        ground1 = WIDTH - 10;
    if(ground2 + WIDTH < 0)
        ground2 = WIDTH - 10;
    if(x == 1) flag = 1;
    //bird->render();
    render();
}

void Game::gameOver()
{
    gameStarted = false;
    Mix_PlayChannel(-1,deadSound,0);
    SDL_RenderCopy(renderer, tex_gameover, NULL, new SDL_Rect{WIDTH / 2 - 96, HEIGHT / 3, 192, 42});
    SDL_RenderPresent(renderer);

    if(gameStarted == false) Mix_HaltMusic();
    SDL_Delay(1000);

    bool wait = true, playagain = false;
    while(wait)
    {

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                wait = false;

            if((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) || (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT))
                {
                    wait = false, playagain = true;
                }
        }
    }
    if(high_score < bird->score) high_score = bird->score;

    //cout << high_score << "\n";
    if(playagain)
        {
            numHeart = 2;
            tmpMusic = 0;
            firstTime = true;
            tempFlag = false;
            Start();
        }
    else
        {

            isRunning = false;
        }
}

void Game::render()
{

    SDL_RenderClear(renderer);

    // background
    SDL_RenderCopy(renderer, tex_background, NULL, NULL);

    // pipes
    for(auto pipe : pipes)
    {
        pipe->render(renderer, tex_pipe);
    }

    // score
    if(bird->score > 9)
    {
        SDL_RenderCopy(renderer, tex_numbers[bird->score / 10 % 10], NULL, new SDL_Rect{WIDTH / 2 - 20, 100, 40, 52});
        SDL_RenderCopy(renderer, tex_numbers[bird->score % 10], NULL, new SDL_Rect{WIDTH / 2 + 20, 100, 40, 52});
    }
    else
        SDL_RenderCopy(renderer, tex_numbers[bird->score], NULL, new SDL_Rect{WIDTH / 2, 100, 40, 52});

    // ground
    SDL_RenderCopy(renderer, tex_ground, NULL, new SDL_Rect{ground1, HEIGHT - GROUND_HEIGHT, WIDTH, GROUND_HEIGHT});
    SDL_RenderCopy(renderer, tex_ground, NULL, new SDL_Rect{ground2, HEIGHT - GROUND_HEIGHT, WIDTH, GROUND_HEIGHT});

    // player
    bird->render();
    renderHighScoreAndHeart();
    SDL_RenderPresent(renderer);
}


void Game::loadTextures()
{
    tex_background = IMG_LoadTexture(renderer, "sprites/background-day.png");
    tex_pipe = IMG_LoadTexture(renderer, "sprites/pipe.png");
    tex_playerMid = IMG_LoadTexture(renderer, "sprites/yellowbird-midflap.png");
    tex_playerUp = IMG_LoadTexture(renderer, "sprites/yellowbird-upflap.png");
    tex_playerDown = IMG_LoadTexture(renderer, "sprites/yellowbird-downflap.png");
    tex_ground = IMG_LoadTexture(renderer, "sprites/base.png");
    tex_gameover = IMG_LoadTexture(renderer, "sprites/gameover.png");


    for(int i = 0; i < 10; i++)
    {
        string path = "sprites/" + to_string(i) + ".png";
        tex_numbers[i] = IMG_LoadTexture(renderer, path.c_str());
    }
}

void Game::Close()
{
    SDL_Quit();
}
