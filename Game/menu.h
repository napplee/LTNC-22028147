#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

class menu{
    SDL_Rect menuRect;
    SDL_Texture *title;
    SDL_Texture *play;
    SDL_Texture *played;
    SDL_Texture *background;
    SDL_Event event;
    int flag = 0;
    bool Menu = true;
    bool exit = false;
    void loadTexture();
    void render(int isClick);
    void eventHandle();
    menu(const char *title, int width, int height);
};

#endif // MENU_H_INCLUDED
