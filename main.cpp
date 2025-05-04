#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <string>
#include "defs.h"
#include "graphics.h"
#include "logic.h"
#include "menu.h"
#include "render.h"

using namespace std;

int NPC_NUM = rand() % 10 + 50;
vector<NPC> npcs;
int wantedNPC;
bool running = true;

int main(int argc, char* argv[])
{
    srand(time(0));

    Graphics graphics;
    graphics.init();

    Mix_Music* bgm = graphics.loadMusic("nhacnen.mp3");
    graphics.play(bgm);

    Mix_Music* winMusic = graphics.loadMusic("WIN.mp3");
    Mix_Music* loseMusic = graphics.loadMusic("LOSE.mp3");

    TTF_Font* font1 = graphics.loadFont("WCManoNegraBoldBta.otf", 40);
    TTF_Font* font2 = graphics.loadFont("WCManoNegraBoldBta.otf", 23);
    TTF_Font* font3 = graphics.loadFont("WCManoNegraBoldBta.otf", 35);

    if (!font1 || !font2 || !font3){
        cout << "SDL_ttf could not initialize!";
        graphics.quit();
        return 1;
    }

    Menu menu;
    bool startGame = menu.showMainMenu(graphics, font1);

    Logic gameLogic;
    gameLogic.createNPC(graphics);

    Sprite sprite;

    graphics.image1 = graphics.loadTexture("image1.png");
    graphics.image2 = graphics.loadTexture("image2.png");

    Renderer renderer;
    renderer.init(graphics.renderer, graphics.image1, graphics.image2);

    sprite.setCustomCursor("aim.png");

    while (running){
        int remaining = gameLogic.getTime();
        int kills = gameLogic.kill();
        int targett = gameLogic.tTarget();

        gameLogic.Events(graphics);
        gameLogic.updateNPC();

        graphics.prepareScene();

        renderer.drawLeftPanel();

        renderer.drawWantedNPC();
        renderer.drawNPCs();

        renderer.renderAll(graphics, font1, font2, font3, remaining, kills, targett);

        if (kills == targett || remaining == 0){
            if (Mix_PlayingMusic()){
                Mix_HaltMusic();
            }

            if (kills == targett){
                if (winMusic){
                    graphics.play(winMusic);
                    SDL_Delay(10);
                }
            } else if (remaining == 0){
                if (loseMusic){
                    graphics.play(loseMusic);
                    SDL_Delay(10);
                }
            }

            bool restart = menu.showEndMenu(graphics, font3);
            if (restart){
                if (Mix_PlayingMusic()){
                    Mix_HaltMusic();
                }
                npcs.clear();
                NPC_NUM = rand() % 10 + 50;
                gameLogic.createNPC(graphics);
                gameLogic.reset();
                graphics.play(bgm);
                continue;
            } else {
                break;
            }
        }

        SDL_RenderPresent(graphics.renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
    TTF_CloseFont(font3);
    renderer.quit();
    graphics.quit();

    return 0;
}

