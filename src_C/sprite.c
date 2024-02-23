#include "sprite.h"

Sprite *SpriteInit(const char *file_name,unsigned int x,unsigned int y,int PV){
    SDL_Surface *surface = IMG_Load(file_name);
    if (surface == NULL){
        printf("Erreur d'importation de l'image \n");
        return NULL;
    }
    Sprite *sprite=(Sprite*)malloc(sizeof(Sprite));
    if (sprite == NULL){
        printf("Erreur malloc sprite\n");
        return NULL;
    }
    sprite->x = x;
    sprite->y = y;
    sprite->surface = surface;
    sprite->PV = PV;
    return sprite;
}

void SpriteDelete(Sprite *sprite){
    SDL_FreeSurface(sprite->surface);
    if (sprite != NULL){
        //free(sprite); //free(): invalid pointer (core dumped)
    }
}

int SpriteMove(Sprite *sprite, int mov_x, int mov_y, int taille){
    if (mov_x > 0){
        if (sprite->x <= WINDOW_WIDTH-sprite->surface->w*taille){
            sprite->x += mov_x;
        }
        else{
            sprite->x += mov_x;
            return 1;
        }
    }
    if (mov_x < 0){
        if (sprite->x > -mov_x){
            sprite->x += mov_x;
        }
        else {
            //sprite->x -= mov_x;
            return 1;
        }
    }
    
    if (mov_y > 0){
        if (sprite->y > WINDOW_HEIGHT) return 0;
        if (sprite->y < WINDOW_HEIGHT-64){ // Surface de sprite aberrante
            sprite->y += mov_y;
        }
        else {
            GameOver = true;
        }
    }
    if (mov_y < 0){
        if (sprite->y > -mov_y){
            sprite->y += mov_y;
        }
    }
    return 0;
}

void SpritesInit(Sprite *sprites,int taille){//Initialisation de la liste des méchants
    int x,y;
    if (NOMBRE_MECHANT >= 45){
        for (x = 0; x < NOMBRE_COLONE; x++){
            for (y = 0; y < NOMBRE_MECHANT/NOMBRE_COLONE; y++){
                if ((x+y*NOMBRE_COLONE)%4==0){ // mob 1
                    sprites[x+y*NOMBRE_COLONE] = *SpriteInit("resources/mobs/méchant1.png",x*ESPACE_COLONE*WINDOW_WIDTH/1980,y*ESPACE_LIGNE*WINDOW_HEIGHT/1240,taille);
                }
                if ((x+y*NOMBRE_COLONE)%4==1) { // mob 2...
                    sprites[x+y*NOMBRE_COLONE] = *SpriteInit("resources/mobs/méchant2.png",x*ESPACE_COLONE*WINDOW_WIDTH/1980,y*ESPACE_LIGNE*WINDOW_HEIGHT/1240,taille);
                }
                if ((x+y*NOMBRE_COLONE)%4==2){
                    sprites[x+y*NOMBRE_COLONE] = *SpriteInit("resources/mobs/méchant1.png",x*ESPACE_COLONE*WINDOW_WIDTH/1980,y*ESPACE_LIGNE*WINDOW_HEIGHT/1240,taille);
                }
                if ((x+y*NOMBRE_COLONE)%4==3){
                    sprites[x+y*NOMBRE_COLONE] = *SpriteInit("resources/mobs/méchant4.png",x*ESPACE_COLONE*WINDOW_WIDTH/1980,y*ESPACE_LIGNE*WINDOW_HEIGHT/1240,taille);
                }
            }
        }
    }
    else {
        printf("Liste des sprites pas assez grande \n");
    }
}

int ListPresent(int i, int killed[], int nb_killed){
    int j;
    for (j = 0; j < nb_killed; j++){
        if (i == killed[j]) return 1;
    }
    return 0;
}

