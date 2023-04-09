#ifndef HEART_H_INCLUDED
#define HEART_H_INCLUDED

class Heart{
public:
    SDL_Rect Pos;
    bool appear = false;
    /*
    void render(SDL_Renderer *renderer, SDL_Texture *tex)
    {
        SDL_RenderCopy(renderer, tex, &bottom_src, &bottom_dst);
        //SDL_RenderCopyEx(renderer, tex, &top_src, &top_dst, 0, NULL, SDL_FLIP_VERTICAL);
    }*/
};

#endif // HEART_H_INCLUDED
