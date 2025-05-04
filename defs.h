#ifndef _DEFS__H
#define _DEFS__H

#include "sprite.h"
#include<vector>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const char* WINDOW_TITLE = "Find!";

const int FRAME_WIDTH = 20;
const int FRAME_HEIGHT = 32;
const int LEFT_BAR = 200;

const SDL_Color black = {0, 0, 0, 255};
const SDL_Color white = {255, 255, 255, 255};
const SDL_Color red = {255, 0, 0, 255};


struct NPC {
  int x, y;
  int dx, dy;
  int frameTimer = 0;
  int frameDelay = 10;
  Sprite sprite;
};

extern int NPC_NUM;

extern vector<NPC> npcs;
extern int wantedNPC;
extern int wantedIndex;
extern bool running;

const char* imageNPC[] = {
    "000.png", "001.png", "002.png", "003.png", "004.png", "005.png", "006.png", "007.png", "008.png", "009.png",
    "010.png", "011.png", "012.png", "013.png", "014.png", "015.png", "016.png", "017.png", "018.png", "019.png",
    "020.png", "021.png", "022.png", "023.png", "024.png", "025.png", "026.png", "027.png", "028.png", "029.png",
    "030.png", "031.png", "032.png", "033.png", "034.png", "035.png", "036.png", "037.png", "038.png", "039.png"
    };

const int NPC_IMAGE_COUNT = sizeof(imageNPC) / sizeof(imageNPC[0]);

const int NPC_CLIPS[][4] = {
    { 0, 0, 20, 32},
    { 20, 0, 20, 32},
    { 40, 0, 20, 32}
};

const int NPC_FRAMES = sizeof(NPC_CLIPS)/sizeof(int)/4;

#endif // _DEFS__H

