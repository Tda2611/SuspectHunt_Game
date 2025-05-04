#ifndef _RENDER__H
#define _RENDER__H

#include "defs.h"
#include "graphics.h"
#include "sprite.h"


struct Renderer {
    Graphics graphics;
    SDL_Renderer* renderer;
    SDL_Texture* image1;
    SDL_Texture* image2;

    // Khởi tạo với renderer và các texture
    void init(SDL_Renderer* ren, SDL_Texture* tex1, SDL_Texture* tex2) {
        renderer = ren;
        image1 = tex1;
        image2 = tex2;
    }

    void drawTextLabels(Graphics& graphics, TTF_Font* font1, TTF_Font* font2, TTF_Font* font3, int timeLeft, int kills, int targetID) {
        graphics.renderText(graphics, "WANTED", font1, black, 35, 150);
        graphics.renderText(graphics, "TIME:", font2, white, 30, 225);
        graphics.renderText(graphics, "KILLS:", font2, white, 115, 225);
        graphics.renderText(graphics, "Target:", font3, black, 25, 315);

        graphics.renderText(graphics, std::to_string(timeLeft).c_str(), font3, white, 33, 245);
        graphics.renderText(graphics, std::to_string(kills).c_str(), font3, white, 120, 245);
        graphics.renderText(graphics, std::to_string(targetID).c_str(), font3, white, 126, 315);
    }

    // Vẽ thanh bên trái
    void drawLeftPanel() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Vẽ đường phân cách bên trái
        SDL_Rect bar = {190, 0, 5, HEIGHT};
        SDL_RenderFillRect(renderer, &bar);

        // Vẽ hình ảnh trên thanh bên trái
        SDL_Rect rect1 = {20, 20, 150, 180};
        SDL_RenderCopy(renderer, image1, nullptr, &rect1);

        // Vẽ hình ảnh thứ hai
        SDL_Rect rect2 = {20, 315, 150, 40};
        SDL_RenderCopy(renderer, image2, nullptr, &rect2);

        // Vẽ các ô cho thời gian và số lần giết
        SDL_Rect time = {20, 220, 65, 80};
        SDL_RenderFillRect(renderer, &time);

        SDL_Rect kills = {105, 220, 65, 80};
        SDL_RenderFillRect(renderer, &kills);
    }

   void drawWantedNPC() {
        if (wantedNPC >= 0 && wantedNPC < npcs.size()) {
            const int scale = 2;
            const SDL_Rect* srcRect = npcs[wantedNPC].sprite.getCurrentClip();

            SDL_Rect dstRect = {
                75,
                70,
                srcRect->w * scale,
                srcRect->h * scale
            };
            SDL_RenderCopy(renderer, npcs[wantedNPC].sprite.texture, srcRect, &dstRect);
        }
    }

    void drawNPCs() {
        for (int i = 0; i < NPC_NUM; i++) {
            const SDL_Rect* srcRect = npcs[i].sprite.getCurrentClip();
            SDL_Rect dstRect = {npcs[i].x, npcs[i].y, srcRect->w, srcRect->h};
            SDL_RenderCopy(renderer, npcs[i].sprite.texture, srcRect, &dstRect);
        }
    }

    // Vẽ toàn bộ cảnh
    void renderAll(Graphics& graphics, TTF_Font* font1, TTF_Font* font2, TTF_Font* font3,
                   int timeLeft, int kills, int targetID) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            drawLeftPanel();
            drawWantedNPC();
            drawNPCs();
            drawTextLabels(graphics, font1, font2, font3, timeLeft, kills, targetID);

            SDL_RenderPresent(renderer);
    }

    // Dọn dẹp tài nguyên khi không còn cần thiết
    void quit() {
        // Hủy tài nguyên SDL
        SDL_DestroyTexture(image1);
        SDL_DestroyTexture(image2);
    }
};

#endif
