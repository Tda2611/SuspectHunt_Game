#ifndef _SPRITE__H
#define _SPRITE__H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

struct Sprite {
    SDL_Texture* texture;
    std::vector<SDL_Rect> clips;
    int currentFrame = 0;

    void init(SDL_Texture* _texture, int frames, const int _clips [][4]) {
        texture = _texture;

        SDL_Rect clip;
        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }
    void tick() {
        currentFrame = (currentFrame + 1) % clips.size();
    }

    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }

    void setCustomCursor(const char* path) {
        SDL_Surface* surface = IMG_Load(path);
        if (!surface) {
            SDL_Log("SDL_image error: %s", IMG_GetError());
            return;
        }

        SDL_Cursor* cursor = SDL_CreateColorCursor(surface, 16, 16);
        SDL_FreeSurface(surface);

        if (!cursor) {
            SDL_Log("Cursor error: %s", SDL_GetError());
            return;
        }

        SDL_SetCursor(cursor);
    }
};

#endif // _SPRITE__H
