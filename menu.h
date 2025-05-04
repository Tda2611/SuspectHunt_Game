#ifndef _MENU__H
#define _MENU__H

#include "graphics.h"
#include "defs.h"
#include "sprite.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

struct Menu {
    Sprite sprite;

    bool showMainMenu(Graphics& graphics, TTF_Font* font1) {
        bool menuRunning = true;
        bool startGame = false;

        SDL_Texture* background = graphics.loadTexture("SUSPECT HUNT!.png");
        if (!background) {
            SDL_Log("Failed to load menu background!");
        }

        while (menuRunning) {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    menuRunning = false;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int x = e.button.x;
                    int y = e.button.y;

                    if (x >= 380 && x <= 494 && y >= 290 && y <= 339) {
                        startGame = true;
                        menuRunning = false;
                    }
                    if (x >= 380 && x <= 476 && y >= 370 && y <= 419) {
                        startGame = false;
                        menuRunning = false;
                    }
                }
            }

            sprite.setCustomCursor("aim.png");

            SDL_RenderCopy(graphics.renderer, background, nullptr, nullptr);

            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            if (mouseX >= 380 && mouseX <= 494 && mouseY >= 290 && mouseY <= 339) {
                        graphics.renderText(graphics, "PLAY", font1, red, 380, 290);
                    } else {
                        graphics.renderText(graphics, "PLAY", font1, black, 380, 290);
                    }
            if (mouseX >= 375 && mouseX <= 471 && mouseY >= 370 && mouseY <= 419) {
                        graphics.renderText(graphics, "EXIT", font1, red, 375, 370);
                    } else {
                        graphics.renderText(graphics, "EXIT", font1, black, 375, 370);
                    }

            SDL_RenderPresent(graphics.renderer);
            SDL_Delay(16);
        }

        SDL_DestroyTexture(background);

        return startGame;
    }

    bool showEndMenu(Graphics& graphics, TTF_Font* font3) {
        SDL_Event event;

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        SDL_SetRenderDrawBlendMode(graphics.renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(graphics.renderer, 128, 128, 128, 180);
        SDL_RenderFillRect(graphics.renderer, nullptr);

        graphics.renderText(graphics, "Try again?", font3, white, 350, 200);
        graphics.renderText(graphics, "YES", font3, white, 350, 250);
        graphics.renderText(graphics, "NO", font3, white, 450, 250);

        SDL_RenderPresent(graphics.renderer);

        while (true) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) return false;
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int x = event.button.x;
                    int y = event.button.y;
                    if (x >= 350 && x <= 430 && y >= 250 && y <= 300) return true;  // YES
                    if (x >= 460 && x <= 520 && y >= 250 && y <= 300) return false; // NO
                }
            }
            SDL_Delay(10);
        }
    }
};

#endif // _MENU__H

