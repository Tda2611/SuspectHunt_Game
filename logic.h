#ifndef _LOGIC__H
#define _LOGIC__H

#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

struct Logic {
  int startTime = SDL_GetTicks();
  int countdownSeconds = 60;
  int countKills = 0;
  int target = rand()% 5 + 15;

  int tTarget(){
    return target;
  }

  // Đếm số đã bắn trúng
  int kill(){
    return countKills;
  }

  // Thêm thời gian
  void addTime(int seconds){
    startTime += seconds * 1000;
  }

  // Đếm ngược thời gian
  int getTime(){
    int currentTime = SDL_GetTicks();
    int elapsed = (currentTime - startTime) / 1000;
    int remaining = countdownSeconds - elapsed;
    if (remaining < 0){
        running = false;
        return 0;
    } else {
        return remaining;
    }
  }

  void createNPC(Graphics& graphics) {

    int imageIndexWanted = rand() % NPC_IMAGE_COUNT;
    SDL_Texture* wantedTexture = graphics.loadTexture(imageNPC[imageIndexWanted]);

    wantedNPC = rand() % NPC_NUM;


    for (int i = 0; i < NPC_NUM; i++) {
        NPC npc;

        int minX = LEFT_BAR;
        int maxX = WIDTH - FRAME_WIDTH;
        int minY = FRAME_HEIGHT;
        int maxY = HEIGHT - FRAME_HEIGHT;

        npc.x = rand() % (maxX - minX + 1) + minX;
        npc.y = rand() % (maxY - minY + 1) + minY;
        npc.dx = rand() % 5 - 2;
        npc.dy = rand() % 5 - 2;

        if(i == wantedNPC){
            npc.sprite.init(wantedTexture, NPC_FRAMES, NPC_CLIPS);
            npc.dx = rand() % 2 - 1;
            npc.dy = rand() % 2 - 1;
        } else {
            int imageIndex;
            do{
                imageIndex = rand() % NPC_IMAGE_COUNT;
            } while (imageIndex == imageIndexWanted);

            SDL_Texture* tex = graphics.loadTexture(imageNPC[imageIndex]);
            npc.sprite.init(tex, NPC_FRAMES, NPC_CLIPS);
        }

        npcs.push_back(npc);
    }
  }

  void updateNPC() {
    for (int i = 0; i < npcs.size(); i++) {
        npcs[i].x += npcs[i].dx;
        npcs[i].y += npcs[i].dy;

        // Va chạm trái - phải
        if (npcs[i].x <= LEFT_BAR) {
            npcs[i].x = LEFT_BAR;
            npcs[i].dx *= -1;
        }
        if (npcs[i].x >= WIDTH - FRAME_WIDTH) {
            npcs[i].x = WIDTH - FRAME_WIDTH;
            npcs[i].dx *= -1;
        }

        // Va chạm trên - dưới
        if (npcs[i].y <= 0) {
            npcs[i].y = 0;
            npcs[i].dy *= -1;
        }
        if (npcs[i].y >= HEIGHT - FRAME_HEIGHT) {
            npcs[i].y = HEIGHT - FRAME_HEIGHT;
            npcs[i].dy *= -1;
        }

        npcs[i].frameTimer++;
        if (npcs[i].frameTimer >= npcs[i].frameDelay) {
            npcs[i].sprite.tick();
            npcs[i].frameTimer = 0;
        }
    }
  }

  void Events(Graphics& graphics) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            if (LEFT_BAR <= mouseX && mouseX <= WIDTH) {
                    if (Mix_Playing(-1) == 0) {
                        Mix_Chunk* gunSound = graphics.loadSound("đạn.mp3");
            if (gunSound != nullptr) {
                    Mix_PlayChannel(-1, gunSound, 0);
                    SDL_Delay(10);
            } else {
                cerr << "Error loading gun sound" << endl;
                }
              }
            }

            bool clickNPC = false;

            for (size_t i = 0; i < npcs.size(); i++) {
                SDL_Rect clip = *npcs[i].sprite.getCurrentClip();
                SDL_Rect npcRect = { npcs[i].x, npcs[i].y, FRAME_WIDTH, FRAME_HEIGHT };

                if (mouseX >= npcRect.x && mouseX <= npcRect.x + npcRect.w &&
                    mouseY >= npcRect.y && mouseY <= npcRect.y + npcRect.h) {
                    clickNPC = true;
                    if (i == wantedNPC) {
                        cout << "CHUAN" << endl;
                        addTime(2);
                        countKills++;
                        npcs.clear();
                        createNPC(graphics);
                    } else {
                        cout << "SAI" << endl;
                        addTime(-3);
                        npcs.clear();
                        createNPC(graphics);
                        }
                    break;
                }
            }

            if (!clickNPC) {
                cout << "SAI" << endl;
                addTime(-3);
                npcs.clear();
                createNPC(graphics);
            }
        }
    }
  }

  void reset() {
    countKills = 0;
    startTime = SDL_GetTicks();
    wantedNPC = rand() % NPC_NUM;
    target = rand() % 5 + 15;
  }

  void run(Graphics& graphics) {
    while (running) {
        Events(graphics);
        updateNPC();
        SDL_Delay(10);
    }
  }
};

#endif // _LOGIC__H
