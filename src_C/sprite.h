#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "config.h"

typedef struct sprite
{
    int x,y;
    SDL_Surface *surface;
    int PV;
} Sprite;

Sprite *SpriteInit(const char *file_name,unsigned int x,unsigned int y,int PV);
void SpriteDelete(Sprite *sprite);
int SpriteMove(Sprite *sprite, int mov_x, int mov_y, int taille);
void SpritesInit(Sprite *sprites, int taille);
int ListPresent(int i, int killed[], int nb_killed);

#endif